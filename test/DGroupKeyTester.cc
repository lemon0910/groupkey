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

TEST(DGroupKey, insertUpdatedData)
{
    DGroupKey<int> groupkey("column1", 10, 0, 1);

    std::vector<RawData<int> > rawDatalist;
    rawDatalist.push_back(RawData<int>(12, 2));
    rawDatalist.push_back(RawData<int>(3, 1));
    rawDatalist.push_back(RawData<int>(100, 4));
    rawDatalist.push_back(RawData<int>(12, 3));

    groupkey.constructThreeVector(rawDatalist);

    Dictionary<int>* otherDictionary = new Dictionary<int>();
    otherDictionary->push_back(3);
    otherDictionary->push_back(17);

    IndexOffset* otherOffset = new IndexOffset();
    otherOffset->push_back(0);
    otherOffset->push_back(1);

    BitCompressedVector* otherPosition = new BitCompressedVector(10);
    otherPosition->push_back(1);
    otherPosition->push_back(2);
    otherPosition->push_back(3);

    boost::shared_ptr<std::vector<uint64_t> > x = groupkey.insertUpdatedData(
        otherDictionary, otherOffset , otherPosition);

    ASSERT_EQ(3, x->size());
    ASSERT_EQ(0, (*x)[0]);
    ASSERT_EQ(0, (*x)[1]);
    ASSERT_EQ(1, (*x)[2]);

    Dictionary<int>* pDictionary = groupkey.getDictionary();
    IndexOffset* pIndex = groupkey.getOffset();
    BitCompressedVector* pPosition = groupkey.getPosition();

    ASSERT_EQ(3, pDictionary->get(0));
    ASSERT_EQ(12, pDictionary->get(1));
    ASSERT_EQ(17, pDictionary->get(2));
    ASSERT_EQ(100, pDictionary->get(3));

    ASSERT_EQ(0, pIndex->get(0));
    ASSERT_EQ(2, pIndex->get(1));
    ASSERT_EQ(3, pIndex->get(2));
    ASSERT_EQ(5, pIndex->get(3));

    ASSERT_EQ(1, pPosition->get(0));
    ASSERT_EQ(5, pPosition->get(1));
    ASSERT_EQ(2, pPosition->get(2));
    ASSERT_EQ(6, pPosition->get(3));
    ASSERT_EQ(7, pPosition->get(4));
    ASSERT_EQ(3, pPosition->get(5));
    ASSERT_EQ(4, pPosition->get(6));
}