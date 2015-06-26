#include <CS/DRowTable.h>
#include <CS/Config.h>

DRowTable::DRowTable(size_t attributeCount, string tableName, uint64_t base):m_attributeCount(attributeCount), m_tableName(tableName), m_base(base)
{
}

void DRowTable::fillOneColumn(string columnName, const uint64_t& itemCount, const vector<uint64_t>& value)
{
    RWMutexLockGuard tmpLock(_mutex , Choice::choiceWrite);
	BitCompressedVector newVector(itemCount);
	for(uint64_t i = 0; i < itemCount; i++)
		newVector.push_back(value[i]);
	m_attributeVector.push_back(newVector);
	m_columnVector.push_back(columnName);
}

vector<uint64_t> DRowTable::getValue(string columnName, const vector<uint64_t> rowID)
{
	BitCompressedVector value = m_attributeVector[caculatePos(columnName)];
	vector<uint64_t> result;
	for(vector<uint64_t>::const_iterator itr = rowID.begin(); itr != rowID.end(); itr++)
	{
		result.push_back(value.get((*itr - m_base)));
	}
	return result;
}

void DRowTable::updateOneColumn(string columnName, const uint64_t& itemCount, const vector<uint64_t>& value)
{
	int64_t pos = caculatePos(columnName);
	if(pos < 0)
		return;
    RWMutexLockGuard tmpLock(_mutex , Choice::choiceWrite);
	m_attributeVector[pos].resize(m_attributeVector[pos].getRows() + itemCount);
	for(uint64_t i = 0; i < itemCount; i++)
		m_attributeVector[pos].push_back(value[i]);
}

vector<vector<uint64_t> > DRowTable::getMultiValue(const vector<string>& columnName, const vector<uint64_t> rowID)
{
	vector<vector<uint64_t> > results;
	for(vector<string>::const_iterator itr = columnName.begin(); itr != columnName.end(); itr++)
	{
		results.push_back(getValue(*itr, rowID));
	}
	return results;
}

uint64_t DRowTable::getColumnRows(string columnName)
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
	cout << "=====DRowTable Print=====" << endl;
	for(uint64_t i = 0; i < m_columnVector.size(); i++)
	{
		cout << "Column: " << m_columnVector[i] << endl;
		BitCompressedVector printVec = m_attributeVector[i];
		printVec.print();
	}
	cout << "=========================" << endl;
}

void DRowTable::refresh(string columnName, const vector<uint64_t>& xVector)
{
	int64_t pos = caculatePos(columnName);
	if(pos < 0)
		return;
    RWMutexLockGuard tmpLock(_mutex , Choice::choiceWrite);
	for(uint64_t i = 0; i < m_attributeVector[pos].getRows(); i++)
	{
		uint64_t former = m_attributeVector[pos].get(i);
		uint64_t increment = xVector[former];
		m_attributeVector[pos].set(i, former + increment);
	}
}
