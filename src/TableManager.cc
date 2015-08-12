#include <TableManager.h>

using namespace std;

TableManager* TableManager::pTableManager = NULL;

TableManager* TableManager::getInstance()
{
    if(pTableManager == NULL)
        pTableManager = new TableManager();

    return pTableManager;
}

TableManager::TableManager()
{
}

TableManager::~TableManager()
{
	for(vector<ColumnTable*>::iterator itr = m_columnTable.begin(); itr != m_columnTable.end(); itr++)
	{
		delete *itr;
	}
	m_columnTable.clear();
	for(vector<DRowTable*>::iterator itr = m_dRowTable.begin(); itr != m_dRowTable.end(); itr++)
	{
		delete *itr;
	}
	m_dRowTable.clear();
}

void TableManager::createColumnTable(const string tableName)
{
	ColumnTable* newTable = new ColumnTable(tableName);
    pushBackColumn(newTable);
}

ColumnTable* TableManager::getColumnTable(const string tableName)
{
	for(vector<ColumnTable*>::iterator itr = m_columnTable.begin(); itr != m_columnTable.end(); itr++)
	{
		if((*itr)->getTableName() == tableName)
		{
			return *itr;
		}
	}
	return NULL;
}

void TableManager::createDRowTable(size_t attributeCount, const string tableName, uint64_t base)
{
	DRowTable* newTable = new DRowTable(attributeCount, tableName, base);
    pushBackRow(newTable);
}

DRowTable* TableManager::getDRowTable(const string tableName)
{
	for(vector<DRowTable*>::iterator itr = m_dRowTable.begin(); itr != m_dRowTable.end(); itr++)
	{
		if((*itr)->getTableName() == tableName)
		{
			return *itr;
		}
	}
	return NULL;
}

void TableManager::pushBackColumn(ColumnTable* pTable)
{
    int64_t len = m_columnTable.size();
    int64_t capacity = m_columnTable.capacity();
    if(capacity - len < 10)
        m_columnTable.reserve(capacity + 10000);

    m_columnTable.push_back(pTable);
}

void TableManager::pushBackRow(DRowTable* pTable)
{
    int64_t len = m_dRowTable.size();
    int64_t capacity = m_dRowTable.capacity();
    if(capacity - len < 10)
        m_dRowTable.reserve(capacity + 100000);

    m_dRowTable.push_back(pTable);
}
