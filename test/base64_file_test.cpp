#include "../include/base64.hpp"

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

TEST(base64_encode_decode, Exe_File)
{
    std::ifstream t("../resources/test.exe");
    std::stringstream buffer;
    buffer << t.rdbuf();
    const std::string expected{buffer.str()};
    ASSERT_EQ(expected.empty(), false);
    const std::string actual{base64::decode({base64::encode({buffer.str()})})};
    ASSERT_EQ(expected, actual);
}   

TEST(base64_encode_decode, UTF8_File)
{
    std::ifstream t("../resources/UTF-8.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    const std::string expected{buffer.str()};
    ASSERT_EQ(expected.empty(), false);
    const std::string actual{base64::decode({base64::encode({buffer.str()})})};
    ASSERT_EQ(expected, actual);
}   

TEST(base64_encode_decode, CP1251_File)
{
    std::ifstream t("../resources/cp-1251.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    const std::string expected{buffer.str()};
    ASSERT_EQ(expected.empty(), false);
    const std::string actual{base64::decode({base64::encode({buffer.str()})})};
    ASSERT_EQ(expected, actual);
}   

TEST(base64_encode_decode, mailFile)
{
    std::ifstream t("../resources/mailFile.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    const std::string expected{buffer.str()};
    ASSERT_EQ(expected.empty(), false);
    const std::string actual{base64::decode({base64::encode({buffer.str()})})};
    ASSERT_EQ(expected, actual);
}
