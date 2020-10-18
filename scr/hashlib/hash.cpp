#include "hash.h"

uint32_t getCRC32(std::istream& in) {
    uint32_t crcTable[256];
    uint32_t crc;

    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crcTable[i] = crc;
    }
    //https://habr.com/ru/post/38622/

    crc = 0xFFFFFFFFUL;

    uint8_t buffer[64'000]; //64кб
    char* bufferToChar = reinterpret_cast<char*>(buffer);
    do {
        in.read(bufferToChar, std::size(buffer));

        for (int i = 0; i < in.gcount(); ++i)
            crc = crcTable[(crc ^ buffer[i]) & 0xFFu] ^ (crc >> 8u);

    } while (in.gcount() == std::size(buffer));

    return crc ^ 0xFFFFFFFFUL;
};

uint32_t getSum32(std::istream& in) {
    uint8_t     buffer[4];
    uint32_t    sum = 0;

    char* bufferToChar = reinterpret_cast<char*>(buffer);
    do {
        in.read(bufferToChar, std::size(buffer));

        unsigned byte_size = 0;
        for (int i = 0; i < in.gcount(); ++i) {
            sum += buffer[i] << byte_size;
            byte_size += 8;
        }

    } while (in.gcount() == std::size(buffer));

    return sum;
}