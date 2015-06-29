#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <ColumnTable.h>
#include <DRowTable.h>
#include <string>

class TableManager
{
private:
	TableManager();
	virtual ~TableManager();
public:
	void createColumnTable(const std::string tableName);
	ColumnTable* getColumnTable(const std::string tableName);
	void createDRowTable(size_t attributeCount, const std::string tableName, uint64_t base);
	DRowTable* getDRowTable(const std::string tableName);
    static TableManager* getInstance();

private:
    static TableManager *pTableManager;
    std::vector<ColumnTable*> m_columnTable;
    std::vector<DRowTable*> m_dRowTable;
};

#endif
