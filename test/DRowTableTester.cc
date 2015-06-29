#include <gtest/gtest.h>
#include <DRowTable.h>

TEST(DRowTable, setAndGet)
{
    DRowTable rowtable(10, "test", 0);
    std::vector<uint64_t> value;
    for(uint64_t i = 0; i < 1000; ++i)
        value.push_back(i);

    rowtable.fillOneColumn("column1", 1000, value);
    vectorptr result = rowtable.getValue("column1", value);

    for(uint64_t i = 0; i < 1000; ++i)
        ASSERT_EQ((*result)[i], i);

    result = rowtable.getValue("column2", value);
    ASSERT_EQ(0, result.get());

    std::vector<uint64_t> temp = value;
    value.clear();
    for(uint64_t i = 1000; i < 2000; ++i)
        value.push_back(i);

    rowtable.fillOneColumn("column2", 1000, value);
    std::vector<std::string> namelist = {"column1", "column2"};
    vectorvectorptr multiresult = rowtable.getMultiValue(namelist, temp);

    ASSERT_EQ(2, multiresult->size());
    for(uint64_t i = 0; i < 1000; ++i)
    {
        ASSERT_EQ(i, (*multiresult)[0][i]);
        ASSERT_EQ(i + 1000, (*multiresult)[1][i]);
    }

    ASSERT_EQ("test", rowtable.getTableName());
    ASSERT_EQ(1000, rowtable.getColumnRows("column1"));
    ASSERT_EQ(1000, rowtable.getColumnRows("column2"));
}

TEST(DRowTable, update)
{
    DRowTable rowtable(100, "test", 0);
    std::vector<uint64_t> temp;
    for(uint64_t i = 0; i < 1000; ++i)
        temp.push_back(i);

    rowtable.fillOneColumn("column1", 1000, temp);
    std::vector<uint64_t> value;
    for(uint64_t i = 0; i < 1000; ++i)
        value.push_back(i + 2008);

    rowtable.updateOneColumn("column1", 1000, value);
    vectorptr result = rowtable.getValue("column1", temp);
    for(uint64_t i = 0; i < 1000; ++i)
        ASSERT_EQ(i + 2008, (*result)[i]);
}

TEST(DRowTable, refresh)
{
    DRowTable rowtable(3, "test", 0);
    std::vector<uint64_t> value;
    for(uint64_t i = 0; i < 3; ++i)
        value.push_back(i);

    rowtable.fillOneColumn("column1", 3, value);

    std::vector<uint64_t> x;
    x.push_back(5);
    x.push_back(11);
    x.push_back(2);

    rowtable.refresh("column1", x);
    vectorptr result = rowtable.getValue("column1", value);

    ASSERT_EQ(5, (*result)[0]);
    ASSERT_EQ(12, (*result)[1]);
    ASSERT_EQ(4, (*result)[2]);
}

