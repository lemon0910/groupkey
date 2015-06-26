#include <ColumnTable.h>

ColumnTable::ColumnTable(std::string tableName):m_tableName(tableName)
{
}

ColumnTable::~ColumnTable()
{
	for(size_t i = 0; i < m_indexVector.size(); i++)
	{
		switch(m_indexVector[i].second)
		{
			case 0:
            {
				DGroupKey<string>* string_ptr = (DGroupKey<string>*)m_columns[i];
				delete string_ptr;
			}
            break;
			case 1:
            {
				DGroupKey<int>* int_ptr = (DGroupKey<int>*)m_columns[i];
				delete int_ptr;
			}
            break;
			case 2:
            {
				DGroupKey<double>* double_ptr = (DGroupKey<double>*)m_columns[i];
				delete double_ptr;
			}
            break;
		}
	}
	m_columns.clear();
	m_indexVector.clear();
}

void ColumnTable::insertOneDGroupKey(void* insertPtr, std::string columnName, uint64_t type)
{
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	m_columns.push_back(insertPtr);
	m_indexVector.push_back(make_pair(columnName, type));
}

pair<void*, uint64_t> ColumnTable::getOneDGroupKey(std::string columnName)
{
	uint64_t pos = getPos(columnName);
	void* result_ptr = m_columns[pos];
	uint64_t result_type = m_indexVector[pos].second;
	return make_pair(result_ptr, result_type);
}

vector<uint64_t> ColumnTable::updateOneDGroupKey(void* updatePtr, string columnName, uint64_t type)
{
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	pair<void*, uint64_t> formerColumn = getOneDGroupKey(columnName);
	switch(type)
	{
		case 0:
        {
			DGroupKey<string>* string_ptr = (DGroupKey<string>*)formerColumn.first;
			return string_ptr->insertUpdatedData(((DGroupKey<string>*)updatePtr)->getDictionary(), ((DGroupKey<string>*)updatePtr)->getOffset(), ((DGroupKey<string>*)updatePtr)->getPosition());
		}
        break;
		case 1:
        {
			return ((DGroupKey<int>*)formerColumn.first)->insertUpdatedData(((DGroupKey<int>*)updatePtr)->getDictionary(), ((DGroupKey<int>*)updatePtr)->getOffset(), ((DGroupKey<int>*)updatePtr)->getPosition());
		}
        break;
		case 2:
        {
			return ((DGroupKey<double>*)formerColumn.first)->insertUpdatedData(((DGroupKey<double>*)updatePtr)->getDictionary(), ((DGroupKey<double>*)updatePtr)->getOffset(), ((DGroupKey<double>*)updatePtr)->getPosition());
		}
        break;
	}
}

string ColumnTable::getTableName()
{
	return m_tableName;
}

void ColumnTable::print()
{
	for(size_t i = 0; i < m_indexVector.size(); i++)
	{
		size_t type = m_indexVector[i].second;
		cout << "+++++++++++++++++++++++++++++++++" << endl;
	    cout << "column: " << m_indexVector[i].first << endl;
		cout << type << endl;
		switch(type)
		{
			case 0:{
				DGroupKey<string>* string_ptr = (DGroupKey<string>*)m_columns[i];
				string_ptr->print();
			}break;
			case 1:{
				DGroupKey<int>* int_ptr = (DGroupKey<int>*)m_columns[i];
				int_ptr->print();
			}break;
			case 2:{
				DGroupKey<double>* double_ptr = (DGroupKey<double>*)m_columns[i];
				double_ptr->print();
			}break;
		}
		cout << "+++++++++++++++++++++++++++++++++" << endl;
	}
}
