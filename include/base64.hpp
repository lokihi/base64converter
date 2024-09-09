#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <stdexcept>

namespace base64
{

namespace detail
{

constexpr std::array<char, 64> encodeTable
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

constexpr std::array<std::uint8_t, 256> decodeTable
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

inline void encodingMainPartString(std::string_view inputString, std::string &outputString)
{
    const size_t sizeEncoded = (inputString.size() + 2) / 3 * 4;
    outputString.reserve(sizeEncoded);

    const uint8_t *inputIterator = reinterpret_cast<const uint8_t *>(&inputString[0]);

    for (size_t i = 0; i < inputString.size() / 3; ++i)
    {
        const uint8_t symbol1 = *inputIterator++;
        const uint8_t symbol2 = *inputIterator++;
        const uint8_t symbol3 = *inputIterator++;

        const std::uint32_t concatenatedBits = (symbol1 << 16) | (symbol2 << 8) | symbol3;

        outputString.push_back(encodeTable[(concatenatedBits >> 18) & 0b0011'1111]);
        outputString.push_back(encodeTable[(concatenatedBits >> 12) & 0b0011'1111]);
        outputString.push_back(encodeTable[(concatenatedBits >> 6) & 0b0011'1111]);
        outputString.push_back(encodeTable[concatenatedBits & 0b0011'1111]);
    }
}

inline void encodingAddPaddingChar(std::string_view inputString, std::string &outputString)
{
    switch (inputString.size() % 3)
    {
    case 0: // Zero padding chars need to be added to encoded string
    {
        break;
    }
    case 1: // One padding char need to be added to encoded string
    {
        const uint8_t sym = inputString.back();
        outputString.push_back(encodeTable[(sym >> 2) & 0b0011'1111]);
        outputString.push_back(encodeTable[(sym << 4) & 0b0011'1111]);
        outputString.push_back('=');
        outputString.push_back('=');
        break;
    }
    case 2: // Two padding chars need to be added to encoded string
    {
        const uint8_t symbol1 = inputString.at(inputString.size()-2);
        const uint8_t symbol2 = inputString.back();
        outputString.push_back(encodeTable[(symbol1 >> 2) & 0b0011'1111]);
        outputString.push_back(encodeTable[(symbol1 << 4 | symbol2 >> 4) & 0b0011'1111]);
        outputString.push_back(encodeTable[(symbol2 << 2) & 0b0011'1111]);
        outputString.push_back('=');
        break;
    }
    default:
    {
        break;
    }
    }
}

inline void decodingMainPartString(std::string_view inputString, size_t numPadding, std::string &outputString)
{
    const size_t sizeDecoded = (inputString.size() / 4 * 3) - numPadding;
    outputString.reserve(sizeDecoded);

    const uint8_t *inputIterator = reinterpret_cast<const uint8_t *>(&inputString[0]);    

    uint8_t currentBlock[4];
    size_t counterBlock = 0;

    size_t blocksAmmount = inputString.size() - (numPadding!=0)*4;

    for (size_t i = 0; i < blocksAmmount; ++i)
    {   
        currentBlock[counterBlock] = *inputIterator++;
        if (currentBlock[counterBlock] != '\n' && currentBlock[counterBlock]!='\r') 
            counterBlock++;
        if (counterBlock == 4)
        {
            const std::uint32_t concatenatedBits = (decodeTable[currentBlock[0]] << 18) | 
                (decodeTable[currentBlock[1]] << 12) | (decodeTable[currentBlock[2]] << 6) | decodeTable[currentBlock[3]];
            outputString.push_back((concatenatedBits >> 16) & 0b1111'1111);
            outputString.push_back((concatenatedBits >> 8) & 0b1111'1111);
            outputString.push_back(concatenatedBits & 0b1111'1111);
            counterBlock = 0;
        }
    }
}

inline void decodingPaddingChar(std::string_view inputString, size_t numPadding, std::string &outputString)
{
    switch (numPadding)
    {
    case 0: // Zero padding char was found at the end of input string
    {
        break;
    }
    case 1: // One padding char was found at the end of input string
    {
        const uint8_t symbol1 = inputString.at(inputString.size()-4);
        const uint8_t symbol2 = inputString.at(inputString.size()-3);
        const uint8_t symbol3 = inputString.at(inputString.size()-2);

        const std::uint32_t concatenatedBits =
            (decodeTable[symbol1] << 18) | (decodeTable[symbol2] << 12) | (decodeTable[symbol3] << 6) | 0x64;

        outputString.push_back((concatenatedBits >> 16) & 0b1111'1111);
        outputString.push_back((concatenatedBits >> 8) & 0b1111'1111);

        break;
    }
    case 2: // Two padding chars were found at the end of input string
    {
        const uint8_t symbol1 = inputString.at(inputString.size()-4);
        const uint8_t symbol2 = inputString.at(inputString.size()-3);

        const std::uint32_t concatenatedBits =
            (decodeTable[symbol1] << 18) | (decodeTable[symbol2] << 12) | 0x64 | 0x64;

        outputString.push_back((concatenatedBits >> 16) & 0b1111'1111);

        break;
    }
    default:
    {
        break;
    }
    }
}
} // namespace detail

inline std::string encode(std::string_view inputString)
{
    const size_t inputDataSize = inputString.size();

    std::string encodedString;

    detail::encodingMainPartString(inputString, encodedString);

    detail::encodingAddPaddingChar(inputString, encodedString);
    
    return encodedString;
}

inline std::string decode(std::string_view inputString, bool& isOk)
{
    isOk = true;

    if (inputString.empty())
    {
        return std::string{};
    }

    const size_t ammountNewline = std::count(inputString.begin(), inputString.end(), '\n');    
    const size_t inputDataSize = inputString.size();

    if ((inputDataSize-ammountNewline)%4 != 0)
    {
        isOk = false;
        return std::string{};
    }
    const size_t numPadding = std::count(inputString.rbegin(), inputString.rbegin() + 4, '=');

    if (numPadding > 2)
    {
        isOk = false;
        return std::string{};
    }

    std::string decodedString;

    detail::decodingMainPartString(inputString, numPadding, decodedString);

    detail::decodingPaddingChar(inputString, numPadding, decodedString);

    return decodedString;
}

inline std::string decode(std::string_view inputString)
{
    bool isOk = false;
    std::string decodedString = decode(inputString, isOk);

    if (!isOk)
        throw std::runtime_error
        {
            "Error decoding base64 string."
        };

    return decodedString;
}

} // namespace base64