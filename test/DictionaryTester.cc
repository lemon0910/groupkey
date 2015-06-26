#include <gtest/gtest.h>
#include <Dictionary.h>
#include <string>

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

TEST(Dictionary, getSurePos)
{
    Dictionary<std::string> dic;
    dic.push_back("abc");
    dic.push_back("bcd");
    dic.push_back("cde");

    ASSERT_EQ(0, dic.getSurePos("abc"));
    ASSERT_EQ(1, dic.getSurePos("bcd"));
    ASSERT_EQ(2, dic.getSurePos("cde"));
}

TEST(Dictionary, existing)
{
    Dictionary<std::string> dic;
    dic.push_back("one");

    ASSERT_TRUE(dic.ifExist("one"));
    ASSERT_FALSE(dic.ifExist("two"));
}

TEST(Dictionary, relation)
{
    Dictionary<uint64_t> dic;

    for(uint64_t i = 0; i < 100000; ++i)
    {
        dic.push_back(i);
    }

    //符合左开右闭原则
    ASSERT_EQ(dic.letGetPos(4), 5);
    ASSERT_EQ(dic.ltGetPos(10), 10);
    ASSERT_EQ(dic.getGetPos(200), 200);
    ASSERT_EQ(dic.gtGetPos(1000), 1001);
}
