#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace base64{

    // Encoding table for base64 converter //
    std::array<char, 64> constexpr encode_table{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', '+', '/'};  


    // ENCODING //
    inline std::string encode(std::string_view input_string){

        // Size of input string //
        const size_t in_data_size = input_string.size();

        // Calculate and reserve place for encoded string //
        size_t size_encoded = (in_data_size +2) / 3 * 4;
        std::string encoded_string;
        encoded_string.reserve(size_encoded);

        // Storing pointer to currently encoded symbol in input string //
        const uint8_t* input_it = reinterpret_cast<const uint8_t*>(&input_string[0]);

        // Iterate over blocks of 3 until the end of the input string //
        for (size_t i = in_data_size / 3;i;--i)
        {

            const uint8_t sym1 = * input_it++;
            const uint8_t sym2 = * input_it++;
            const uint8_t sym3 = * input_it++;

            std::uint32_t const concat_bits = (sym1 << 16) | (sym2 << 8) | sym3;

            encoded_string.push_back(encode_table[(concat_bits >> 18) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(concat_bits >> 12) & 0b0011'1111]);
            encoded_string.push_back(encode_table[(concat_bits >> 6) & 0b0011'1111]);
            encoded_string.push_back(encode_table[concat_bits & 0b0011'1111]);

        }

        // Adding special padding characters //
        switch (in_data_size%3){
            case 0:{

                break;

            }
            case 1:{

                const uint8_t sym = * input_it++;
                encoded_string.push_back(encode_table[(sym >> 2) & 0b0011'1111]);
                encoded_string.push_back(encode_table[(sym << 4) & 0b0011'1111]);
                encoded_string.push_back('=');
                encoded_string.push_back('=');
                break;

            }
            case 2:{

                const uint8_t sym1 = * input_it++;
                const uint8_t sym2 = * input_it++;
                encoded_string.push_back(encode_table[(sym1 >> 2) & 0b0011'1111]);
                encoded_string.push_back(encode_table[(sym1 << 4 | sym2 >> 4) & 0b0011'1111]);
                encoded_string.push_back(encode_table[(sym2 << 2) & 0b0011'1111]);
                encoded_string.push_back('=');
                break;

            }
        }

        return encoded_string;
        
    }
}