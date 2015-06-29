#include <gtest/gtest.h>
#include <IndexOffset.h>

TEST(IndexOffset, pushAndGet)
{
    IndexOffset index;

    for(uint64_t i = 0; i < 1000; ++i)
    {
        index.push_back(i);
        ASSERT_EQ(i, index.get(i));
    }

    ASSERT_EQ(0, index.get(1000));
    ASSERT_EQ(1000, index.getRows());
}