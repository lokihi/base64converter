#include "../include/base64.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(base64encode, InputEmpty)
{
    const std::string expected{};
    const std::string actual{base64::encode({})};
    ASSERT_EQ(expected, actual);
}

TEST(base64encode, SingleSymbolInput)
{
    const std::string expected{"bw=="};
    const std::string actual{base64::encode({"o"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64encode, DoubleSymbolInput)
{
    const std::string expected{"b2s="};
    const std::string actual{base64::encode({"ok"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64encode, TripleSymbolInput)
{
    const std::string expected{"b2tp"};
    const std::string actual{base64::encode({"oki"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64encode, LongInput)
{
    const std::string expected{"YmFzZTY0IGVuY29kZXI="};
    const std::string actual{base64::encode({"base64 encoder"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64encode, RealyLongInput)
{
    const std::string expected{"VGhpcyBpcyBhIHJlYWxseSBsb25nIHN0cmluZyB0byB0ZXN0IHRoaXMgYWJzb2x1dGVseSBiZWF1dGlmdWwgYmFzZTY0IGVuY29kZXI="};
    const std::string actual{base64::encode({"This is a really long string to test this absolutely beautiful base64 encoder"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, OutputEmpty)
{
    const std::string expected{};
    const std::string actual{base64::decode({})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, SingleSymbolOutput)
{
    const std::string expected{"o"};
    const std::string actual{base64::decode({"bw=="})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, DoubleSymbolOutput)
{
    const std::string expected{"ok"};
    const std::string actual{base64::decode({"b2s="})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, TripleSymbolOutput)
{
    const std::string expected{"oki"};
    const std::string actual{base64::decode({"b2tp"})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, LongOutput)
{
    const std::string expected{"base64 encoder"};
    const std::string actual{base64::decode({"YmFzZTY0IGVuY29kZXI="})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, RealyLongOutput)
{
    const std::string expected{"This is a really long string to test this absolutely beautiful base64 encoder"};
    const std::string actual{base64::decode({"VGhpcyBpcyBhIHJlYWxseSBsb25nIHN0cmluZyB0byB0ZXN0IHRoaXMgYWJzb2x1dGVseSBiZWF1dGlmdWwgYmFzZTY0IGVuY29kZXI="})};
    ASSERT_EQ(expected, actual);
}

TEST(base64decode, FlagErrorAmmountOfSymbols)
{
    bool flag;
    const std::string decoded{base64::decode({"123"}, flag)};
    ASSERT_FALSE(flag);
}

TEST(base64decode, FlagErrorNumPadding)
{
    bool flag;
    const std::string decoded{base64::decode({"12345==="}, flag)};
    ASSERT_FALSE(flag);
}

TEST(base64decode, FlagCorrectAmmountOfSymbols)
{
    bool flag;
    const std::string decoded{base64::decode({"1234"},flag)};
    ASSERT_TRUE(flag);
}

TEST(base64decode, FlagCorrectNumPadding)
{
    bool flag;
    const std::string decoded{base64::decode({"123456=="},flag)};
    ASSERT_TRUE(flag);
}
