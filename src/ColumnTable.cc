#include <ColumnTable.h>
#include <Logging.h>

ColumnTable::ColumnTable(const std::string tableName) : m_tableName(tableName)
{
}

ColumnTable::~ColumnTable()
{
	for(size_t i = 0; i < m_indexVector.size(); i++)
	{
		switch(m_indexVector[i].second)
		{
			case STRINGTYPE:
            {
				DGroupKey<std::string>* string_ptr = (DGroupKey<std::string>*)m_columns[i];
				delete string_ptr;
			}
            break;
			case INTTYPE:
            {
				DGroupKey<int>* int_ptr = (DGroupKey<int>*)m_columns[i];
				delete int_ptr;
			}
            break;
			case DOUBLETYPE:
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

void ColumnTable::insertOneDGroupKey(void* insertPtr, std::string columnName, const Type type)
{
    RWMutexLockGuard tmpLock(_mutex , WRITE);
	m_columns.push_back(insertPtr);
	m_indexVector.push_back(make_pair(columnName, type));
}

std::pair<void*, Type> ColumnTable::getOneDGroupKey(const std::string columnName)
{
	uint64_t pos = getPos(columnName);
	void* result_ptr = m_columns[pos];
	Type result_type = m_indexVector[pos].second;
	return std::make_pair(result_ptr, result_type);
}

boost::shared_ptr<std::vector<uint64_t> > ColumnTable::updateOneDGroupKey(void* updatePtr, const std::string columnName, const Type type)
{
    RWMutexLockGuard tmpLock(_mutex , WRITE);
    std::pair<void*, Type> formerColumn = getOneDGroupKey(columnName);
	switch(type)
	{
		case STRINGTYPE:
        {
			DGroupKey<std::string>* string_ptr = (DGroupKey<std::string>*)formerColumn.first;
			return string_ptr->insertUpdatedData(((DGroupKey<std::string>*)updatePtr)->getDictionary(), ((DGroupKey<std::string>*)updatePtr)->getOffset(), ((DGroupKey<std::string>*)updatePtr)->getPosition());
		}
        break;
		case INTTYPE:
        {
			return ((DGroupKey<int>*)formerColumn.first)->insertUpdatedData(((DGroupKey<int>*)updatePtr)->getDictionary(), ((DGroupKey<int>*)updatePtr)->getOffset(), ((DGroupKey<int>*)updatePtr)->getPosition());
		}
        break;
		case DOUBLETYPE:
        {
			return ((DGroupKey<double>*)formerColumn.first)->insertUpdatedData(((DGroupKey<double>*)updatePtr)->getDictionary(), ((DGroupKey<double>*)updatePtr)->getOffset(), ((DGroupKey<double>*)updatePtr)->getPosition());
		}
        break;
        default:
            return boost::shared_ptr<std::vector<uint64_t> >();
	}
}

std::string ColumnTable::getTableName()
{
	return m_tableName;
}

void ColumnTable::print()
{
	for(size_t i = 0; i < m_indexVector.size(); i++)
	{
		Type type = m_indexVector[i].second;
		LOG_INFO << "+++++++++++++++++++++++++++++++++";
	    LOG_INFO << "column: " << m_indexVector[i].first;
		//LOG_INFO << type;
		switch(type)
		{
			case STRINGTYPE:
            {
				DGroupKey<std::string>* string_ptr = (DGroupKey<std::string>*)m_columns[i];
				string_ptr->print();
			}
            break;
			case INTTYPE:
            {
				DGroupKey<int>* int_ptr = (DGroupKey<int>*)m_columns[i];
				int_ptr->print();
			}
            break;
			case DOUBLETYPE:
            {
				DGroupKey<double>* double_ptr = (DGroupKey<double>*)m_columns[i];
				double_ptr->print();
			}
            break;
		}
		LOG_INFO << "+++++++++++++++++++++++++++++++++";
	}
}
