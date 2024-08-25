#include <gtest/gtest.h>

#include "../include/base64.hpp"
#include <string>

// TEST FOR EMPTY INPUT //
TEST(base64encode, InputEmpty)
{
    std::string const expected{};
    std::string const actual{base64::encode({})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR SINGLE SYMBOL INPUT STRING //
TEST(base64encode, SingleSymbolInput)
{
    std::string const expected{"bw=="};
    std::string const actual{base64::encode({"o"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR TWO SYMBOL INPUT STRING //
TEST(base64encode, DoubleSymbolInput)
{
    std::string const expected{"b2s="};
    std::string const actual{base64::encode({"ok"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR TRIPLE SYMBOL INPUT STRING //
TEST(base64encode, TripleSymbolInput)
{
    std::string const expected{"b2tp"};
    std::string const actual{base64::encode({"oki"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR LONG STRING //
TEST(base64encode, LongInput)
{
    std::string const expected{"YmFzZTY0IGVuY29kZXI="};
    std::string const actual{base64::encode({"base64 encoder"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR REALY LONG STRING //
TEST(base64encode, RealyLongInput)
{
    std::string const expected{"VGhpcyBpcyBhIHJlYWxseSBsb25nIHN0cmluZyB0byB0ZXN0IHRoaXMgYWJzb2x1dGVseSBiZWF1dGlmdWwgYmFzZTY0IGVuY29kZXI="};
    std::string const actual{base64::encode({"This is a really long string to test this absolutely beautiful base64 encoder"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR EMPTY OUTPUT //
TEST(base64decode, OutputEmpty)
{
    std::string const expected{};
    std::string const actual{base64::decode({})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR SINGLE SYMBOL OUTPUT STRING //
TEST(base64decode, SingleSymbolOutput)
{
    std::string const expected{"o"};
    std::string const actual{base64::decode({"bw=="})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR TWO SYMBOL OUTPUT STRING //
TEST(base64decode, DoubleSymbolOutput)
{
    std::string const expected{"ok"};
    std::string const actual{base64::decode({"b2s="})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR TRIPLE SYMBOL OUTPUT STRING //
TEST(base64decode, TripleSymbolOutput)
{
    std::string const expected{"oki"};
    std::string const actual{base64::decode({"b2tp"})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR LONG STRING //
TEST(base64decode, LongOutput)
{
    std::string const expected{"base64 encoder"};
    std::string const actual{base64::decode({"YmFzZTY0IGVuY29kZXI="})};
    ASSERT_EQ(expected, actual);
}

// TEST FOR REALY LONG STRING //
TEST(base64decode, RealyLongOutput)
{
    std::string const expected{"This is a really long string to test this absolutely beautiful base64 encoder"};
    std::string const actual{base64::decode({"VGhpcyBpcyBhIHJlYWxseSBsb25nIHN0cmluZyB0byB0ZXN0IHRoaXMgYWJzb2x1dGVseSBiZWF1dGlmdWwgYmFzZTY0IGVuY29kZXI="})};
    ASSERT_EQ(expected, actual);
}
