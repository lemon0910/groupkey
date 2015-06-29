#include <gtest/gtest.h>
#include <TableManager.h>

TEST(TableManager, Singleton)
{
    TableManager *pManager = TableManager::getInstance();
    ASSERT_TRUE(pManager != NULL);

    TableManager *p2Manager = TableManager::getInstance();
    ASSERT_EQ(pManager, p2Manager);
}

TEST(TableManager, ColumnTable)
{
    TableManager *pManager = TableManager::getInstance();
    pManager->createColumnTable("name");
    pManager->createColumnTable("age");

    ASSERT_TRUE(NULL != pManager->getColumnTable("name"));
    ASSERT_TRUE(NULL != pManager->getColumnTable("age"));
    ASSERT_EQ(NULL, pManager->getColumnTable("scores"));
}

TEST(TableManager, DRowTable)
{
    TableManager *pManager = TableManager::getInstance();
    pManager->createDRowTable(1, "name", 0);
    pManager->createDRowTable(2, "age", 100);

    ASSERT_TRUE(NULL != pManager->getDRowTable("name"));
    ASSERT_TRUE(NULL != pManager->getDRowTable("age"));
    ASSERT_EQ(NULL, pManager->getDRowTable("scores"));
}