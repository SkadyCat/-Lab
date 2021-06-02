#ifndef DTCONTROLLER_H
#define DTCONTROLLER_H


/**
 * @brief The DTController class
 *
 * its just for controll the Decoding tube
 */
class DTController
{
public:
    DTController();

    static int pointerIndex;
    static unsigned char data[];
    static unsigned char path[];

    /**
     * @brief Ox2Binary convert the hexadecimal to bianary
     * such as:
     * the 0xc0 -> 1100 0000
     * @param value the value that be converted
     */
    static int* Ox2Binary(int value);
    /**
     * @brief DTWrite write value to the Decoding Tube
     * @param value the writting value
     */
    static void DTWrite(int SCLK,int DIO,int value);

    /**
     * @brief Bright bright the decodding tube
     * @param path the index of the decoding tube
     * @param value the value that you want to show value
     */
    static void Bright(int SCLK,int RCLK,int DIO,int path,int value);


    /**
     * i don't want to describe this func because you know
     * it should play the role that you think
     * @brief BrightAll
     * @param SCLK
     * @param RCLK
     * @param DIO
     * @param showData
     * @return
     */
    static void BrightAll(int SCLK,int RCLK,int DIO,int showData[],int * index);
};

#endif // DTCONTROLLER_H
