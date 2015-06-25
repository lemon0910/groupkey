#include <gtest/gtest.h>
#include <Dictionary.h>

TEST(Dictionary, pushAndGet)
{
    Dictionary<uint64_t> dic;

    for(uint64_t i = 1000; i <= 60000; ++i)
    {
        dic.push_back(i);
        ASSERT_EQ(i, dic.get(i - 1000));
    }

    ASSERT_EQ(60000 - 1000 + 1, dic.getRows());
}


