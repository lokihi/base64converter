#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <stdexcept>

namespace base64
{

// Encoding table for base64 converter //
std::array<char, 64> constexpr encodeTable
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

// Decoding table for base 64 converter //
std::array<std::uint8_t, 256> constexpr decodeTable
{
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x3E, 0x64, 0x64, 0x64, 0x3F, 
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x64, 0x64, 0x64, 0x64, 0x64, 
    0x64, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64
};

// ENCODING //
inline std::string encode(std::string_view inputString)
{

    // Size of input string //
    const size_t inputDataSize = inputString.size();

    // Calculate place for encoded string //
    const size_t sizeEncoded = (inputDataSize + 2) / 3 * 4;

    // Reserve place for encoded string
    std::string encodedString;
    encodedString.reserve(sizeEncoded);

    // Storing pointer to currently encoded symbol in input string //
    const uint8_t *inputIterator = reinterpret_cast<const uint8_t *>(&inputString[0]);

    // Iterate over blocks of 3 until the end of the input string //
    for (size_t i = inputDataSize / 3; i; --i)
    {

        const uint8_t symbol1 = *inputIterator++;
        const uint8_t symbol2 = *inputIterator++;
        const uint8_t symbol3 = *inputIterator++;

        std::uint32_t const concatenatedBits = (symbol1 << 16) | (symbol2 << 8) | symbol3;

        encodedString.push_back(encodeTable[(concatenatedBits >> 18) & 0b0011'1111]);
        encodedString.push_back(encodeTable[(concatenatedBits >> 12) & 0b0011'1111]);
        encodedString.push_back(encodeTable[(concatenatedBits >> 6) & 0b0011'1111]);
        encodedString.push_back(encodeTable[concatenatedBits & 0b0011'1111]);
    }

    // Adding special padding characters //
    switch (inputDataSize % 3)
    {
    case 0:
    {

        break;
    }
    case 1:
    {

        const uint8_t sym = *inputIterator++;
        encodedString.push_back(encodeTable[(sym >> 2) & 0b0011'1111]);
        encodedString.push_back(encodeTable[(sym << 4) & 0b0011'1111]);
        encodedString.push_back('=');
        encodedString.push_back('=');
        break;
    }
    case 2:
    {

        const uint8_t symbol1 = *inputIterator++;
        const uint8_t symbol2 = *inputIterator++;
        encodedString.push_back(encodeTable[(symbol1 >> 2) & 0b0011'1111]);
        encodedString.push_back(encodeTable[(symbol1 << 4 | symbol2 >> 4) & 0b0011'1111]);
        encodedString.push_back(encodeTable[(symbol2 << 2) & 0b0011'1111]);
        encodedString.push_back('=');
        break;
    }
    }

    return encodedString;
}

inline std::string decode(std::string_view inputString)
{

    if (inputString.empty())
    {
        return std::string{};
    }

    // Size of input string //
    const size_t inputDataSize = inputString.size();

    // Ammount of paddings in input string //
    const size_t numPadding = std::count(inputString.rbegin(), inputString.rbegin() + 4, '=');
    const size_t numNewLine = std::count(inputString.begin(), inputString.end(), '\n');
    const size_t numReturn = std::count(inputString.begin(), inputString.end(), '\r');

    // Check, if ammount of padding symbols is correct (< 2) //
    if (numPadding > 2)
    {
        throw std::runtime_error{
            "Invalid base64 string. Couldn't resolve ammount of paddinngs."};
    }

    // Calculate and reserve place for decoded string //
    size_t sizeDecoded = (inputDataSize / 4 * 3) - numPadding;
    std::string decodedString;
    decodedString.reserve(sizeDecoded);

    // Storing pointer to currently decoded symbol in input string //
    const uint8_t *inputIterator = reinterpret_cast<const uint8_t *>(&inputString[0]);    

    uint8_t currentBlock[4];
    int counterBlock = 0;

    // Iterate over blocks of 4 until the end of the input string //
    for (size_t i = 0; i < inputDataSize - (numPadding!=0)*4; i++)
    {   
        currentBlock[counterBlock] = *inputIterator++;
        if (currentBlock[counterBlock] != '\n' && currentBlock[counterBlock]!='\r') counterBlock++;
        if (counterBlock == 4)
        {
        std::uint32_t const concatenatedBits =
            (decodeTable[currentBlock[0]] << 18) | (decodeTable[currentBlock[1]] << 12) | (decodeTable[currentBlock[2]] << 6) | decodeTable[currentBlock[3]];
        decodedString.push_back((concatenatedBits >> 16) & 0b1111'1111);
        decodedString.push_back((concatenatedBits >> 8) & 0b1111'1111);
        decodedString.push_back(concatenatedBits & 0b1111'1111);
        counterBlock = 0;
        }
    }

    // Work with end of the base64 encoded string //
    switch (numPadding)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        const uint8_t symbol1 = *inputIterator++;
        const uint8_t symbol2 = *inputIterator++;
        const uint8_t symbol3 = *inputIterator++;

        std::uint32_t const concatenatedBits =
            (decodeTable[symbol1] << 18) | (decodeTable[symbol2] << 12) | (decodeTable[symbol3] << 6) | 0x64;

        decodedString.push_back((concatenatedBits >> 16) & 0b1111'1111);
        decodedString.push_back((concatenatedBits >> 8) & 0b1111'1111);

        break;
    }
    case 2:
    {
        const uint8_t symbol1 = *inputIterator++;
        const uint8_t symbol2 = *inputIterator++;

        std::uint32_t const concatenatedBits =
            (decodeTable[symbol1] << 18) | (decodeTable[symbol2] << 12) | 0x64 | 0x64;

        decodedString.push_back((concatenatedBits >> 16) & 0b1111'1111);

        break;
    }
    }

    return decodedString;
}
} // namespace base64