#ifndef COLUMNTABLE_H
#define COLUMNTABLE_H

#include <string>

#include <DGroupKey.h>
#include <RWMutex.h>

class ColumnTable
{
private:

    typedef std::vector<std::pair<std::string, uint64_t> > vector_t;

public:

    ColumnTable(std::string tableName);
    virtual ~ColumnTable();
    void insertOneDGroupKey(void* insertPtr, std::string columnName, uint64_t type);
    std::pair<void*, uint64_t> getOneDGroupKey(std::string columnName);
    std::vector<uint64_t> updateOneDGroupKey(void* updatePtr, std::string columnName, uint64_t type);
    std::string getTableName();
    void print();

    inline uint64_t getPos(std::string columnName)//precise search, if not exist, return -1
    {
        for(vector_t::iterator itr = m_indexVector.begin(); itr != m_indexVector.end();
            itr++)
        {
            if((*itr).first == columnName)
                return distance(m_indexVector.begin(), itr);
        }
        return -1;
    }

private:

    std::string m_tableName;
    std::vector<void*> m_columns;
    std::vector_t m_indexVector;
    RWMutexLock _mutex;
};

#endif
