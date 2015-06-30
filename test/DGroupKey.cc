#include <gtest/gtest.h>
#include <DGroupKey.h>

TEST(DGroupKey, construct)
{
    DGroupKey<int> groupkey("column1", 10, 0, 1);

    std::vector<RawData<int> > rawDatalist;
    rawDatalist.push_back(RawData<int>(12, 2));
    rawDatalist.push_back(RawData<int>(3, 1));
    rawDatalist.push_back(RawData<int>(100, 4));
    rawDatalist.push_back(RawData<int>(12, 3));

    groupkey.constructThreeVector(rawDatalist);

    ASSERT_EQ("column1", groupkey.getName());
    ASSERT_EQ(0, groupkey.getBase());

    Dictionary<int>* pDictionary = groupkey.getDictionary();
    IndexOffset* pIndex = groupkey.getOffset();
    BitCompressedVector* pPosition = groupkey.getPosition();

    ASSERT_EQ(3, pDictionary->get(0));
    ASSERT_EQ(12, pDictionary->get(1));
    ASSERT_EQ(100, pDictionary->get(2));

    ASSERT_EQ(0, pIndex->get(0));
    ASSERT_EQ(1, pIndex->get(1));
    ASSERT_EQ(3, pIndex->get(2));

    ASSERT_EQ(1, pPosition->get(0));
    ASSERT_EQ(2, pPosition->get(1));
    ASSERT_EQ(3, pPosition->get(2));
    ASSERT_EQ(4, pPosition->get(3));
}