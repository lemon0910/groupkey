#include <DRowTable.h>

using namespace std;

DRowTable::DRowTable(size_t attributeCount, const std::string tableName, uint64_t base) : m_attributeCount(attributeCount), m_tableName(tableName), m_base(base)
{
}

void DRowTable::fillOneColumn(const string columnName, const uint64_t& itemCount, const vector<uint64_t>& value)
{
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	BitCompressedVector newVector(itemCount);
	for(uint64_t i = 0; i < itemCount; i++)
		newVector.push_back(value[i]);
	m_attributeVector.push_back(newVector);
	m_columnVector.push_back(columnName);
}

vectorptr DRowTable::getValue(const string columnName, const vector<uint64_t>& rowID)
{
    int index = caculatePos(columnName);
    if(index == -1)
    {
        return vectorptr();
    }

	BitCompressedVector& value = m_attributeVector[caculatePos(columnName)];
	vectorptr result(new vector<uint64_t>());
	for(vector<uint64_t>::const_iterator itr = rowID.begin(); itr != rowID.end(); itr++)
	{
		result->push_back(value.get((*itr - m_base)));
	}
	return result;
}

void DRowTable::updateOneColumn(const string columnName, const uint64_t& itemCount, const vector<uint64_t>& value)
{
	int64_t pos = caculatePos(columnName);
	if(pos < 0)
		return;
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	m_attributeVector[pos].resize(m_attributeVector[pos].getRows() + itemCount);
	for(uint64_t i = 0; i < itemCount; i++)
		m_attributeVector[pos].push_back(value[i]);
}

vectorvectorptr DRowTable::getMultiValue(const vector<string>& columnName, const vector<uint64_t>& rowID)
{
	vectorvectorptr results(new std::vector<std::vector<uint64_t> >());
	for(vector<string>::const_iterator itr = columnName.begin(); itr != columnName.end(); itr++)
	{
		results->push_back(*getValue(*itr, rowID));
	}
	return results;
}

uint64_t DRowTable::getColumnRows(const string columnName)
{
	int64_t pos = caculatePos(columnName);
	return m_attributeVector[pos].getRows();
}

string DRowTable::getTableName()
{
	return m_tableName;
}

void DRowTable::print()
{
	LOG_INFO << "=====DRowTable Print=====";
	for(uint64_t i = 0; i < m_columnVector.size(); i++)
	{
		LOG_INFO << "Column: " << m_columnVector[i];
		BitCompressedVector printVec = m_attributeVector[i];
		printVec.print();
	}
	LOG_INFO << "=========================";
}

void DRowTable::refresh(const string columnName, const vector<uint64_t>& xVector)
{
	int64_t pos = caculatePos(columnName);
	if(pos < 0)
		return;
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	for(uint64_t i = 0; i < m_attributeVector[pos].getRows(); i++)
	{
		uint64_t former = m_attributeVector[pos].get(i);
		uint64_t increment = xVector[former];
		m_attributeVector[pos].set(i, former + increment);
	}
}
