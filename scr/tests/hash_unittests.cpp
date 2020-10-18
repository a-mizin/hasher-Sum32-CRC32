#include "gtest/gtest.h"

#include "../hashlib/hash.h"

#include <sstream>

//            Sum32 TESTS
TEST(Sum32_test, empty_file)
{
    std::stringstream ss("");

    EXPECT_EQ(0, getSum32(ss));
}

TEST(Sum32_test, NUL_character)
{
    std::stringstream ss("\0");

    EXPECT_EQ(0, getSum32(ss));
}

TEST(Sum32_test, single_char)
{
    std::stringstream ss("a");

    EXPECT_EQ('a', getSum32(ss));
}

TEST(Sum32_test, random_file_sum)
{
    std::stringstream ss("aaaa");
    uint32_t result = 'a' | 'a' << 8 | 'a' << 16 | 'a' << 24;

    EXPECT_EQ(result, getSum32(ss));
}

//            CRC32 TESTS
TEST(CRC32_test, empty_file)
{
    std::stringstream ss("");

    EXPECT_EQ(0, getCRC32(ss));
}

TEST(CRC32_test, single_char)
{
    std::stringstream ss("a");

    EXPECT_EQ(3904355907, getCRC32(ss));
}

TEST(CRC32_test, random_file)
{
    std::stringstream ss("dsafgkhdfhskgsdf");

    EXPECT_EQ(3709972603, getCRC32(ss));
}