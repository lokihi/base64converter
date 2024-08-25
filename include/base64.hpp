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
    std::array<char, 64> constexpr encode_table{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                                'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                                'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5',
                                                '6', '7', '8', '9', '+', '/'};

    std::array<std::uint8_t, 256> constexpr decode_table{0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x3E, 0x64, 0x64,
                                                         0x64, 0x3F, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
                                                         0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x1A, 0x1B, 0x1C,
                                                         0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E,
                                                         0x2F, 0x30, 0x31, 0x32, 0x33, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
                                                         0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64};

    // ENCODING //
    inline std::string encode(std::string_view input_string)
    {

        // Size of input string //
        const size_t in_data_size = input_string.size();

        // Calculate and reserve place for encoded string //
        size_t size_encoded = (in_data_size + 2) / 3 * 4;
        std::string encoded_string;
        encoded_string.reserve(size_encoded);

        // Storing pointer to currently encoded symbol in input string //
        const uint8_t *input_it = reinterpret_cast<const uint8_t *>(&input_string[0]);

        // Iterate over blocks of 3 until the end of the input string //
        for (size_t i = in_data_size / 3; i; --i)
        {

            const uint8_t sym1 = *input_it++;
            const uint8_t sym2 = *input_it++;
            const uint8_t sym3 = *input_it++;

            std::uint32_t const concat_bits = (sym1 << 16) | (sym2 << 8) | sym3;

            encoded_string.push_back(encode_table[(concat_bits >> 18) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(concat_bits >> 12) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(concat_bits >> 6) & 0b0011'1111]);
            encoded_string.push_back(encode_table[concat_bits & 0b0011'1111]);
        }

        // Adding special padding characters //
        switch (in_data_size % 3)
        {
        case 0:
        {

            break;
        }
        case 1:
        {

            const uint8_t sym = *input_it++;
            encoded_string.push_back(encode_table[(sym >> 2) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(sym << 4) & 0b0011'1111]);
            encoded_string.push_back('=');
            encoded_string.push_back('=');
            break;
        }
        case 2:
        {

            const uint8_t sym1 = *input_it++;
            const uint8_t sym2 = *input_it++;
            encoded_string.push_back(encode_table[(sym1 >> 2) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(sym1 << 4 | sym2 >> 4) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(sym2 << 2) & 0b0011'1111]);
            encoded_string.push_back('=');
            break;
        }
        }

        return encoded_string;
    }

    inline std::string decode(std::string_view input_string)
    {

        if (input_string.empty())
        {
            return std::string{};
        }

        if (input_string.size() % 4 != 0)
        {
            throw std::runtime_error{
                "Invalid base64 data. Couldn't resolve ammount of symbols."};
        }

        // Size of input string //
        const size_t in_data_size = input_string.size();

        // Ammount of paddings in input string //
        const size_t numPadding = std::count(input_string.rbegin(), input_string.rbegin() + 4, '=');

        if (numPadding > 2)
        {
            throw std::runtime_error{
                "Invalid base64 string. Couldn't resolve ammount of paddinngs."};
        }

        // Calculate and reserve place for decoded string //
        size_t size_decoded = (in_data_size / 4 * 3) - numPadding;
        std::string decoded_string;
        decoded_string.reserve(size_decoded);

        // Storing pointer to currently decoded symbol in input string //
        const uint8_t *input_it = reinterpret_cast<const uint8_t *>(&input_string[0]);

        // Iterate over blocks of 4 until the end of the input string //
        for (size_t i = (in_data_size - numPadding) / 4; i; --i)
        {

            const uint8_t sym1 = *input_it++;
            const uint8_t sym2 = *input_it++;
            const uint8_t sym3 = *input_it++;
            const uint8_t sym4 = *input_it++;

            std::uint32_t const concat_bytes =
                (decode_table[sym1] << 18) | (decode_table[sym2] << 12) | (decode_table[sym3] << 6) | decode_table[sym4];

            decoded_string.push_back((concat_bytes >> 16) & 0b1111'1111);
            decoded_string.push_back((concat_bytes >> 8) & 0b1111'1111);
            decoded_string.push_back(concat_bytes & 0b1111'1111);
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
            const uint8_t sym1 = *input_it++;
            const uint8_t sym2 = *input_it++;
            const uint8_t sym3 = *input_it++;

            std::uint32_t const concat_bytes =
                (decode_table[sym1] << 18) | (decode_table[sym2] << 12) | (decode_table[sym3] << 6) | 0x64;

            decoded_string.push_back((concat_bytes >> 16) & 0b1111'1111);
            decoded_string.push_back((concat_bytes >> 8) & 0b1111'1111);

            break;
        }
        case 2:
        {
            const uint8_t sym1 = *input_it++;
            const uint8_t sym2 = *input_it++;

            std::uint32_t const concat_bytes =
                (decode_table[sym1] << 18) | (decode_table[sym2] << 12) | 0x64 | 0x64;

            decoded_string.push_back((concat_bytes >> 16) & 0b1111'1111);

            break;
        }
        }

        return decoded_string;
    }
}