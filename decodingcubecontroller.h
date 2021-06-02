#ifndef DECODINGCUBECONTROLLER_H
#define DECODINGCUBECONTROLLER_H


class DecodingCubeController
{
public:
    DecodingCubeController();

    static unsigned char* data;
    static unsigned char* path;

    /**
     * @brief Ox2Binary convert the hexadecimal to bianary
     * such as:
     * the 0xc0 -> 1100 0000
     * @param value the value that be converted
     */
    static void Ox2Binary(int value);
    /**
     * @brief DTWrite write value to the Decoding Tube
     * @param value the writting value
     */
    static void DTWrite(int value);

    /**
     * @brief Bright bright the decodding tube
     * @param path the index of the decoding tube
     * @param value the value that you want to show value
     */
    static void Bright(int path,int value);
};

#endif // DECODINGCUBECONTROLLER_H
