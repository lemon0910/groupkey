#ifndef ROWTABLE_H
#define ROWTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "BitCompressedVector.h"
#include "RWMutex.h"

using namespace std;

class DRowTable
{
public:

	DRowTable(size_t attributeCount , string tableName , uint64_t base);
	virtual ~DRowTable(){}
	void fillOneColumn(string columnName, const uint64_t& itemCount, const vector<uint64_t>& value);
	//TODO 压缩行表之后再传，提供compressed vector的拷贝

	//SQL执行函数
	//PROJECT
	vector<uint64_t> getValue(string columnName, const vector<uint64_t> rowID);
	vector<vector<uint64_t> > getMultiValue(const vector<string>& columnName, const vector<uint64_t> rowID);
	//TODO 其他的物理算子包括AGG聚合函数的实现
	//ENDSQL执行函数

	void updateOneColumn(string columnName, const uint64_t& itemCount, const vector<uint64_t>& value);//append V vector
	void refresh(string columnName, const vector<uint64_t>& xVector);
	uint64_t getColumnRows(string columnName);
	string getTableName();
	void print();

private:

	inline int64_t caculatePos(string columnName)
	{
		vector<string>::iterator itr = find(m_columnVector.begin(), m_columnVector.end(), columnName);
		if(itr == m_columnVector.end())
			return -1;
		else
			return distance(m_columnVector.begin(), itr);
	}

private:

	uint64_t m_attributeCount;
	string m_tableName;
	uint64_t m_base;
	vector<BitCompressedVector> m_attributeVector;
	vector<string> m_columnVector;
	RWMutexLock _mutex;
};
#endif
