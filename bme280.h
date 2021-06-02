#ifndef BME280_H
#define BME280_H
#define BME280_DIG_T1_LSB_REG 0x88
#define BME280_DIG_T1_MSB_REG 0x89
#define BME280_DIG_T2_LSB_REG 0x8A
#define BME280_DIG_T2_MSB_REG 0x8B
#define BME280_DIG_T3_LSB_REG 0x8C
#define BME280_DIG_T3_MSB_REG 0x8D

#define BME280_DIG_P1_LSB_REG 0x8E
#define BME280_DIG_P1_MSB_REG 0x8F
#define BME280_DIG_P2_LSB_REG 0x90
#define BME280_DIG_P2_MSB_REG 0x91
#define BME280_DIG_P3_LSB_REG 0x92
#define BME280_DIG_P3_MSB_REG 0x93
#define BME280_DIG_P4_LSB_REG 0x94
#define BME280_DIG_P4_MSB_REG 0x95
#define BME280_DIG_P5_LSB_REG 0x96
#define BME280_DIG_P5_MSB_REG 0x97
#define BME280_DIG_P6_LSB_REG 0x98
#define BME280_DIG_P6_MSB_REG 0x99
#define BME280_DIG_P7_LSB_REG 0x9A
#define BME280_DIG_P7_MSB_REG 0x9B
#define BME280_DIG_P8_LSB_REG 0x9C
#define BME280_DIG_P8_MSB_REG 0x9D
#define BME280_DIG_P9_LSB_REG 0x9E
#define BME280_DIG_P9_MSB_REG 0x9F
#define BME280_DIG_H1_REG 0xA1
#define BME280_CHIP_ID_REG 0xD0
#define BME280_RST_REG 0xE0
#define BME280_DIG_H2_LSB_REG 0xE1
#define BME280_DIG_H2_MSB_REG 0xE2
#define BME280_DIG_H3_REG 0xE3
#define BME280_DIG_H4_MSB_REG 0xE4
#define BME280_DIG_H4_LSB_REG 0xE5
#define BME280_DIG_H5_MSB_REG 0xE6
#define BME280_DIG_H6_REG 0xE7
#define BME280_CTRL_HUMIDITY_REG 0xF2
#define BME280_STAT_REG 0xF3
#define BME280_CTRL_MEAS_REG 0xF4
#define BME280_CONFIG_REG 0xF5
#define BME280_PRESSURE_MSB_REG 0xF7
#define BME280_PRESSURE_LSB_REG 0xF8
#define BME280_PRESSURE_XLSB_REG 0xF9
#define BME280_TEMPERATURE_MSB_REG 0xFA
#define BME280_TEMPERATURE_LSB_REG 0xFB
#define BME280_TEMPERATURE_XLSB_REG 0xFC
#define BME280_HUMIDITY_MSB_REG 0xFD
#define BME280_HUMIDITY_LSB_REG 0xFE

#include<QObject>
//author ljy qq:874212844
class BME280:public QObject
{

public:
    static BME280* Instance;
    enum PRESSURE_OVERSAMPLING
     {
     PRESSURE_OVERSAMPLING_SKIPPED = 0x00,
     PRESSURE_OVERSAMPLING_PLUS_ONE = 0x01,
     PRESSURE_OVERSAMPLING_PLUS_TWO = 0x02,
     PRESSURE_OVERSAMPLING_PLUS_FOUR = 0x03,
     PRESSURE_OVERSAMPLING_PLUS_EIGHT = 0x04,
     PRESSURE_OVERSAMPLING_PLUS_SIXTEEN = 0x05
     };
     enum TEMPERATURE_OVERSAMPLING
     {
     TEMPERATURE_OVERSAMPLING_SKIPPED = 0x00,
     TEMPERATURE_OVERSAMPLING_PLUS_ONE = 0x01,
     TEMPERATURE_OVERSAMPLING_PLUS_TWO = 0x02,
     TEMPERATURE_OVERSAMPLING_PLUS_FOUR = 0x03,
     TEMPERATURE_OVERSAMPLING_PLUS_EIGHT = 0x04,
     TEMPERATURE_OVERSAMPLING_PLUS_SIXTEEN = 0x05
     };
     enum MODE_OF_PRESSURE_TEMPERATUR
     {
     MODE_OF_PRESSURE_TEMPERATUR_SLEEP = 0x00,
     MODE_OF_PRESSURE_TEMPERATUR_FORCED = 0x01,
     MODE_OF_PRESSURE_TEMPERATUR_MORMAL = 0x03
     };
     enum HUMIDITY_OVERSAMPLING
     {
     HUMIDITY_OVERSAMPLING_SKIPPED = 0x00,
     HUMIDITY_OVERSAMPLING_PLUS_ONE = 0x01,
     HUMIDITY_OVERSAMPLING_PLUS_TWO = 0x02,
     HUMIDITY_OVERSAMPLING_PLUS_FOUR = 0x03,
     HUMIDITY_OVERSAMPLING_PLUS_EIGHT = 0x04,
     HUMIDITY_OVERSAMPLING_PLUS_SIXTEEN = 0x05
     };
     struct Calibration //修正系数
     {
            uint16_t dig_T1;
          int16_t dig_T2;
          int16_t dig_T3;
          uint16_t dig_P1;
          int16_t dig_P2;
          int16_t dig_P3;
          int16_t dig_P4;
          int16_t dig_P5;
          int16_t dig_P6;
          int16_t dig_P7;
          int16_t dig_P8;
          int16_t dig_P9;
          uint8_t dig_H1;
          int16_t dig_H2;
          uint8_t dig_H3;
          int16_t dig_H4;
          int16_t dig_H5;
          uint8_t dig_H6;
     };

    explicit BME280(int Address = 0x76);
    void bme_init(); //初始化
    float getTemperature(); //获取温度（摄氏度）
    float getPressure(); //获取压强（百帕）
    float getHumidity(); //获取湿度（百分数）
private:
    int address;
    int fd;
    Calibration calibration;
    int32_t _tFine;

};

#endif // BME280_H
