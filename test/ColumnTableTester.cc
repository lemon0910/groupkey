#include <gtest/gtest.h>
#include <ColumnTable.h>

TEST(ColumnTable, setAndGet)
{
    DGroupKey<int> groupkey("column1", 1000, 0, 0);
    ColumnTable columntable("table1");
    columntable.insertOneDGroupKey((void*)&groupkey, "column1", INVALID);
    std::pair<void*, Type> result = columntable.getOneDGroupKey("column1");

    ASSERT_EQ((void*)&groupkey, result.first);
    ASSERT_EQ(INVALID, result.second);
}