
#include "bme280.h"
#include <QDebug>


#include <QtGlobal>
#include"writetool.h"
#ifdef Q_OS_LINUX

#include "wiringPi.h"
#include "wiringPiI2C.h"

#endif

BME280* BME280::Instance = NULL;
BME280::BME280(int Address):address(Address) //开启 iic
{ //wiringPiSetup();


    #ifdef Q_OS_LINUX
        fd = wiringPiI2CSetup(Address);
        qDebug()<<"setup";
        Instance = this;

    #endif

}
void BME280::bme_init() //初始化，每次读取之前调用
{
 uchar uc;
 char c;

#ifdef Q_OS_LINUX

 uc = TEMPERATURE_OVERSAMPLING_PLUS_TWO<<5 |
PRESSURE_OVERSAMPLING_PLUS_TWO<<2 | MODE_OF_PRESSURE_TEMPERATUR_FORCED;
 wiringPiI2CWriteReg8(fd, BME280_CTRL_MEAS_REG,uc);
 wiringPiI2CWriteReg8(fd, BME280_CTRL_HUMIDITY_REG,
HUMIDITY_OVERSAMPLING_PLUS_TWO);
 calibration.dig_T1 = static_cast<unsigned short>(wiringPiI2CReadReg16(fd,
BME280_DIG_T1_LSB_REG));
 calibration.dig_T2 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_T2_LSB_REG));
 calibration.dig_T3 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_T3_LSB_REG));
 calibration.dig_P1 = static_cast<unsigned short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P1_LSB_REG));
 calibration.dig_P2 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P2_LSB_REG));
 calibration.dig_P3 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P3_LSB_REG));
 calibration.dig_P4 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P4_LSB_REG));
 calibration.dig_P5 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P5_LSB_REG));
 calibration.dig_P6 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P6_LSB_REG));
 calibration.dig_P7 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P7_LSB_REG));
 calibration.dig_P8 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P8_LSB_REG));
 calibration.dig_P9 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_P9_LSB_REG));
 calibration.dig_H1 = static_cast<unsigned char>(wiringPiI2CReadReg8(fd,
BME280_DIG_H1_REG));
 calibration.dig_H2 = static_cast<short>(wiringPiI2CReadReg16(fd,
BME280_DIG_H2_LSB_REG));
 calibration.dig_H3 = static_cast<unsigned char>(wiringPiI2CReadReg8(fd,
 BME280_DIG_H3_REG));
  c = static_cast<char>(wiringPiI2CReadReg8(fd, BME280_DIG_H4_LSB_REG));
  calibration.dig_H4 = static_cast<short>((wiringPiI2CReadReg8(fd,
 BME280_DIG_H4_MSB_REG) << 4) | (c & 0x0F));
  calibration.dig_H5 = static_cast<short>((wiringPiI2CReadReg8(fd,
 BME280_DIG_H5_MSB_REG) << 4) | ((c >> 4) & 0x0F));
  calibration.dig_H6 = static_cast<unsigned char>(wiringPiI2CReadReg8(fd,
 BME280_DIG_H3_REG));
  delayMicroseconds(20); //数据手册中写了一个最低延时，这里粗略延时 20us

#endif

 }

float BME280::getTemperature() //读取温度值
{


#ifdef Q_OS_LINUX
    int32_t temp_raw,var1,var2;
    float temperature;
    temp_raw = (static_cast<int>(wiringPiI2CReadReg8(fd,
   BME280_TEMPERATURE_MSB_REG) << 12)) | (static_cast<int>(wiringPiI2CReadReg8(fd,
   BME280_TEMPERATURE_LSB_REG) << 4)) | ((wiringPiI2CReadReg8(fd,
   BME280_TEMPERATURE_XLSB_REG) >> 4) & 0x0F); //读寄存器
    var1 = ((((temp_raw>>3) - (calibration.dig_T1<<1))) *
   (calibration.dig_T2)) >> 11;
    var2 = (((((temp_raw>>4) - (calibration.dig_T1)) * ((temp_raw>>4) -
   (calibration.dig_T1))) >> 12) * (calibration.dig_T3)) >> 14; //换算、修正公式见 bme280 数据手册
    _tFine = var1 + var2; //修正值赋值
    temperature = (_tFine * 5 + 128) >> 8;
    temperature = temperature / 100;
    return temperature;

#endif
    return 0;
}

float BME280::getPressure() //获取压强值
{
    #ifdef Q_OS_LINUX
    int32_t pres_raw;
    double var1, var2, pressure;
    pres_raw = (static_cast<int>(wiringPiI2CReadReg8(fd,
   BME280_PRESSURE_MSB_REG) << 12)) | (static_cast<int>(wiringPiI2CReadReg8(fd,
   BME280_PRESSURE_LSB_REG) << 4)) | ((wiringPiI2CReadReg8(fd,
   BME280_PRESSURE_XLSB_REG) >> 4) & 0x0F); //读寄存器
   //修正压强值，换算公式见 bme280 数据手册
    var1 = _tFine / 2.0 - 64000.0;
    var2 = var1 * var1 * calibration.dig_P6 / 32768.0;
    var2 = var2 + var1 * calibration.dig_P5 * 2.0;
    var2 = var2 / 4.0 + calibration.dig_P4 * 65536.0;
    var1 = (calibration.dig_P3 * var1 * var1 / 524288.0 + calibration.dig_P2 *
   var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * calibration.dig_P1;
    if(var1 == 0.0)
    pressure = 0;
    else
    {
    pressure = 1048576.0 - pres_raw;
    pressure = ((pressure - var2 / 4096.0) * 6250.0) / var1;
    var1 = calibration.dig_P9 * pressure * pressure / 2147483648.0;
    var2 = pressure * calibration.dig_P8 / 32768.0;
    pressure = pressure + (var1 + var2 + calibration.dig_P7) / 16.0;
    }
    pressure = pressure / 100;
    return static_cast<float>(pressure);
    #endif

    return 0;
}

float BME280::getHumidity() //获取湿度值
{

#ifdef Q_OS_LINUX

    int32_t hum_raw;
    double humidity;
    hum_raw = (static_cast<int>(wiringPiI2CReadReg8(fd, BME280_HUMIDITY_MSB_REG)
   << 8)) | wiringPiI2CReadReg8(fd, BME280_HUMIDITY_LSB_REG); //读相应寄存器
    humidity = _tFine - 76800.0;
    humidity = (hum_raw - (calibration.dig_H4 * 64.0 + calibration.dig_H5 /
   16384.0 * humidity)) * (calibration.dig_H2 / 65536.0 * (1.0 + calibration.dig_H6
   / 67108864.0 * humidity * (1.0 + calibration.dig_H3 / 67108864.0 * humidity)));
    humidity = humidity * (1.0 - calibration.dig_H1 * humidity / 524288.0); //换算公式见 bme280 数据手册
    if(humidity<0) humidity = 0;
    if(humidity>100) humidity = 100;
    return static_cast<float>(humidity);
#endif

    return 0;
}
