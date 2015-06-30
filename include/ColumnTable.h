#ifndef COLUMNTABLE_H
#define COLUMNTABLE_H

#include <string>

#include <DGroupKey.h>
#include <RWMutex.h>

enum Type{STRINGTYPE, INTTYPE, DOUBLETYPE, INVALID};

class ColumnTable
{
private:

    typedef std::vector<std::pair<std::string, Type> > vector_t;

public:

    ColumnTable(const std::string tableName);
    virtual ~ColumnTable();
    void insertOneDGroupKey(void* insertPtr, std::string columnName, const Type type);
    std::pair<void*, Type> getOneDGroupKey(const std::string columnName);
    boost::shared_ptr<std::vector<uint64_t> > updateOneDGroupKey(void* updatePtr, const std::string columnName, const Type type);
    std::string getTableName();
    void print();

    inline int getPos(std::string columnName)//precise search, if not exist, return -1
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
    vector_t m_indexVector;
    RWMutexLock _mutex;
};

#endif
