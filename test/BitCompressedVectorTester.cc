#include <BitCompressedVector.h>
#include <gtest/gtest.h>
#include <vector>

TEST(BitCompressedVector, checkSize)
{
    BitCompressedVector v(100);
    ASSERT_TRUE(v.checkSize(90));
    ASSERT_FALSE(v.checkSize(49331));
}

TEST(BitCompressedVector, maxValue)
{
    BitCompressedVector v(100);
    ASSERT_LT(8000, v.maxValue());
    ASSERT_GT(9000, v.maxValue());
}

TEST(BitCompressedVector, setAndGet)
{
    BitCompressedVector v(1);
    v.push_back(12);
    ASSERT_EQ(12, v.get(0));
    ASSERT_EQ(0, v.get(1));
    v.push_back(100);
    ASSERT_EQ(100, v.get(1));
    v.push_back(100000);
    ASSERT_EQ(100000, v.get(2));
    ASSERT_EQ(3, v.getRows());
    v.push_back(100000000);
    ASSERT_EQ(100000000, v.get(3));
}

TEST(BitCompressedVector, reSizeAndGetRange)
{
    BitCompressedVector v(1000000);

    for(uint64_t i = 0; i < 1000000; ++i)
    {
        v.push_back(i);
        //ASSERT_EQ(i, v.get(i));
    }

    for(uint64_t i = 0; i < 1000000; ++i)
    {
        ASSERT_EQ(i, v.get(i));
    }

    std::vector<uint64_t> result = v.getRange(500, 500000);
    for(uint64_t i = 500; i <= 500000; ++i)
    {
        ASSERT_EQ(i, result[i - 500]);
    }

    v.clear();
}