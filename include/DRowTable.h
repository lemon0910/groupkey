#ifndef ROWTABLE_H
#define ROWTABLE_H

#include <string>
#include <vector>
#include <algorithm>

#include <BitCompressedVector.h>
#include <RWMutex.h>
#include <Logging.h>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<std::vector<uint64_t> > vectorptr;
typedef boost::shared_ptr<std::vector<std::vector<uint64_t> > > vectorvectorptr;

class DRowTable
{
public:

	DRowTable(size_t attributeCount , const std::string tableName , uint64_t base);
	virtual ~DRowTable(){}
	void fillOneColumn(const std::string columnName, const uint64_t& itemCount, const std::vector<uint64_t>& value);
	//TODO 压缩行表之后再传，提供compressed vector的拷贝

	//SQL执行函数
	//PROJECT
    vectorptr getValue(const std::string columnName, const std::vector<uint64_t>& rowID);
	vectorvectorptr getMultiValue(const std::vector<std::string>& columnName, const std::vector<uint64_t>& rowID);
	//TODO 其他的物理算子包括AGG聚合函数的实现
	//ENDSQL执行函数

	void updateOneColumn(const std::string columnName, const uint64_t& itemCount, const std::vector<uint64_t>& value);//append V vector
	void refresh(const std::string columnName, const std::vector<uint64_t>& xVector);
	uint64_t getColumnRows(const std::string columnName);
    std::string getTableName();
	void print();

private:

	inline int64_t caculatePos(const std::string columnName)
	{
        std::vector<std::string>::iterator itr = std::find(m_columnVector.begin(), m_columnVector.end(), columnName);
		if(itr == m_columnVector.end())
			return -1;
		else
			return std::distance(m_columnVector.begin(), itr);
	}

    void pushBackAttribute(BitCompressedVector& v);
    void pushBackColumn(std::string str);

private:

	uint64_t m_attributeCount;
    std::string m_tableName;
	uint64_t m_base;
    std::vector<BitCompressedVector> m_attributeVector;
    std::vector<std::string> m_columnVector;
	RWMutexLock _mutex;
};
#endif
