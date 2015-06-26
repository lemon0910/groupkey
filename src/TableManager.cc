#include <CS/TableManager.h>

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

void TableManager::createColumnTable(string tableName)
{
	ColumnTable* newTable = new ColumnTable(tableName);
	m_columnTable.push_back(newTable);
}

ColumnTable* TableManager::getColumnTable(string tableName)
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

void TableManager::createDRowTable(size_t attributeCount, string tableName, uint64_t base)
{
	DRowTable* newTable = new DRowTable(attributeCount, tableName, base);
	m_dRowTable.push_back(newTable);
}

DRowTable* TableManager::getDRowTable(string tableName)
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
