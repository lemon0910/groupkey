#include <BitCompressedVector.h>

BitCompressedVector::BitCompressedVector(uint64_t rowCount):m_pData(NULL), m_rowCount(rowCount), m_currentRow(0)
{
	if(rowCount > 0)
	{
	    m_bitForItem = log2(m_rowCount);
		if(m_bitForItem + 7 <= 64)
			m_bitForItem += 7;
		m_blockNumber = m_rowCount * m_bitForItem / bitWidth + 1;
		m_size = m_blockNumber * sizeof(storage_unit_t);
		m_pData = allocMemory(m_blockNumber);
	}
	else
	{
		LOG_INFO << "BitCompressedVector::BitCompressedVector() error";
	}
}

BitCompressedVector::BitCompressedVector(const BitCompressedVector& other)
{
	m_bitForItem = other.m_bitForItem;
	m_size = other.m_size;
	m_rowCount = other.m_rowCount;
	m_currentRow = 0;
	m_blockNumber = other.m_blockNumber;

	m_pData = allocMemory(m_blockNumber);
	memcpy(m_pData, other.m_pData, m_blockNumber * sizeof(storage_unit_t));
}

BitCompressedVector& BitCompressedVector::operator=(const BitCompressedVector& other)
{
	if(this == &other)
		return *this;

	m_bitForItem = other.m_bitForItem;
	m_size = other.m_size;
	m_rowCount = other.m_rowCount;
	m_currentRow = 0;
	m_blockNumber = other.m_blockNumber;

	storage_unit_t* newData;
	newData = allocMemory(m_blockNumber);
	memcpy(newData, other.m_pData, m_blockNumber * sizeof(storage_unit_t));
	free(m_pData);
	m_pData = newData;
}

BitCompressedVector::~BitCompressedVector()
{
	reset();
}

bool BitCompressedVector::checkSize(uint64_t totalRows)
{
	if(m_bitForItem * totalRows < m_size)
		return true;
	else
		return false;
}

void BitCompressedVector::resize(uint64_t totalRows) // keep the old data
{
	if(checkSize(totalRows))
	{
		m_rowCount = totalRows;
		return;
	}

	storage_unit_t* newData;
	uint64_t blockNumber = totalRows * m_bitForItem / bitWidth + 1;

	newData = allocMemory(blockNumber);
	memcpy(newData, m_pData, m_blockNumber * sizeof(storage_unit_t));//old data copy
	free(m_pData);
	m_pData = newData;
	m_size = blockNumber * sizeof(storage_unit_t);
	m_rowCount = totalRows;
	m_blockNumber = blockNumber;
}

void BitCompressedVector::clear() //capacity remains, clear all the old data
{
	m_currentRow = 0;
	memset(m_pData, 0 , m_blockNumber * sizeof(storage_unit_t));
}

void BitCompressedVector::reset()
{
	free(m_pData);
	m_pData = NULL;
	m_currentRow = 0;
	m_rowCount = 0;
	m_blockNumber = 0;
	m_size = 0;
}

void BitCompressedVector::resetBitForItem(uint64_t value)
{
	uint64_t bitForItem = log2(value);
	if(bitForItem + 7 <= 64)
		bitForItem += 7;
	
	storage_unit_t* newData;
	blockNumber = m_rowCount * bitForItem / bitWidth + 1;
	newData = allocMemory(blockNumber);
	for(uint64_t rowID = 0; rowID <= m_currentRow; ++rowID)
	{
		uint64_t tempvalue = get(rowID);
		uint64_t offset = (bitForItem * rowID) % bitWidth;;
		uint64_t block = (bitForItem * rowID) / bitWidth;

		uint64_t bounds = bitWidth - offset;
		uint64_t baseMask = (1ull << bitForItem) - 1ull;
		uint64_t mask;

		if(bounds >= bitForItem) //stay in one block
		{
			mask = ~(baseMask << (bitWidth - bitForItem - offset));
			newData[block] &= mask;
			newData[block] |= (((storage_unit_t)value & baseMask) << (bitWidth - bitForItem - offset));
		}
		else //span 2 blocks
		{
			//fisrt block
			mask = ~(baseMask >> (bitForItem - bounds));
			newData[block] &= mask;
			newData[block] |= (((storage_unit_t)value & baseMask) >> (bitForItem - bounds));

			//second block
			mask = ~(baseMask << (bitWidth - bitForItem + bounds));
			newData[block + 1] &= mask;
			newData[block + 1] |= (((storage_unit_t)value & baseMask) << (bitWidth - bitForItem + bounds));
		}
	}
	
	m_bitForItem = bitForItem;
	m_blockNumber = blockNumber;
	m_size = m_blockNumber * sizeof(storage_unit_t);
}

void BitCompressedVector::set(uint64_t rowID, uint64_t value)
{
	uint64_t maxvalue = (1ull << m_bitForItem) - 1ull;
	if(m_bitForItem != 64 && value > maxvalue)
	{
		resetBitForItem(value);
	}
	
	if(!checkSize(rowID))
		resize(rowID + 10000);
	
	uint64_t offset = blockOffset(rowID);
	uint64_t block = blockPosition(rowID);

	uint64_t bounds = bitWidth - offset;
	uint64_t baseMask = (1ull << m_bitForItem) - 1ull;
	uint64_t mask;

	if(bounds >= m_bitForItem) //stay in one block
	{
		mask = ~(baseMask << (bitWidth - m_bitForItem - offset));
		m_pData[block] &= mask;
		m_pData[block] |= (((storage_unit_t)value & baseMask) << (bitWidth - m_bitForItem - offset));
	}
	else //span 2 blocks
	{
		//fisrt block
		mask = ~(baseMask >> (m_bitForItem - bounds));
		m_pData[block] &= mask;
		m_pData[block] |= (((storage_unit_t)value & baseMask) >> (m_bitForItem - bounds));

		//second block
		mask = ~(baseMask << (bitWidth - m_bitForItem + bounds));
		m_pData[block + 1] &= mask;
		m_pData[block + 1] |= (((storage_unit_t)value & baseMask) << (bitWidth - m_bitForItem + bounds));
	}
}

void BitCompressedVector::push_back(uint64_t value)
{
	uint64_t rowID = m_currentRow;
	set(rowID, value);
	m_currentRow++;
}

uint64_t BitCompressedVector::get(uint64_t rowID)
{
	if(rowID > m_rowCount)
	{
		LOG_INFO << "invalid rowID";
		return 0;
	}
	
	uint64_t result;
	uint64_t offset = blockOffset(rowID);
	uint64_t block = blockPosition(rowID);

	uint64_t bounds = bitWidth - offset;
	uint64_t baseMask = (1ull << m_bitForItem) - 1ull;

	if(bounds >= m_bitForItem)
	{
		result = (((m_pData[block]) >> (bitWidth - (offset + m_bitForItem))) & baseMask);
	}
	else
	{
		uint64_t mask = baseMask >> (m_bitForItem - bounds);
		result = m_pData[block] & mask;
		result = result << (m_bitForItem - bounds);

		//second block
		mask = baseMask >> bounds;
		result |= ((m_pData[block + 1] >> (bitWidth - (m_bitForItem - bounds))) & mask);
	}

	return result;
}

vector<uint64_t> BitCompressedVector::getRange(uint64_t rowIDUpper, uint64_t rowIDLower)
{

	if(rowIDUpper > rowIDLower || rowIDUpper < 0 || rowIDLower > m_rowCount)
		return vector<uint64_t>();

	else if(rowIDUpper == rowIDLower)
		return vector<uint64_t>(1, get(rowIDUpper));

	else
	{
		vector<uint64_t> result;

		for(uint64_t currentRow = rowIDUpper; currentRow <= rowIDLower; currentRow++)
		{
			result.push_back(get(currentRow));
		}
		return result;
	}
}

uint64_t BitCompressedVector::getSize()
{
	return m_size;
}
uint64_t BitCompressedVector::getRows()
{
	return m_rowCount;
}

void BitCompressedVector::shrinkSize(uint64_t totalRows) // delete the half of old data
{
	storage_unit_t* newData;
	uint64_t blockNumber = totalRows * m_bitForItem / bitWidth + 1;

	newData = allocMemory(blockNumber);
	memcpy(newData, m_pData, m_blockNumber * sizeof(storage_unit_t));//old half of data's copy
	free(m_pData);
	m_pData = newData;
	m_size = blockNumber * sizeof(storage_unit_t);
	m_rowCount = totalRows;
	m_blockNumber = blockNumber;
}

void BitCompressedVector::posShrink(uint64_t pos)
{
	shrinkSize(pos);
	m_currentRow = pos;
}

void BitCompressedVector::print()
{
	for(uint64_t i = 0; i < m_currentRow; i++)
		LOG_INFO << "BitCompressedVector[" << i << "]: " << get(i);
}
