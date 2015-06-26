#include <Logging.h>
#include <IndexOffset.h>

IndexOffset::IndexOffset() : m_offsetVector(10000)
{
}

IndexOffset::IndexOffset(uint64_t n) : m_offsetVector(n)
{
}

IndexOffset::~IndexOffset()
{
	clear();
}

void IndexOffset::push_back(uint64_t index)
{
	m_offsetVector.push_back(index);
}

void IndexOffset::print()
{
    m_offsetVector.print();
}

uint64_t IndexOffset::get(uint64_t pos)
{
    if(pos >= getRows())
    {
        LOG_INFO << "out of range";
        return 0;
    }

	return m_offsetVector.get(pos);
}

uint64_t IndexOffset::getRows()
{
	return m_offsetVector.getRows();
}

/*
uint64_t IndexOffset::findBinarySplitPos(uint64_t positionIndex)
{
	uint64_t pos = 0;
	for(auto itr = m_offsetVector.begin(); itr != m_offsetVector.end(); itr++)
	{
		if(*itr > positionIndex)
			return pos - 1;
		else
			pos++;
	}

    return pos;
}
*/

void IndexOffset::offsetShrink(uint64_t pos, uint64_t count)
{
    m_offsetVector.posShrink(pos);
    m_offsetVector.push_back(count);
}

void IndexOffset::clear()
{
	m_offsetVector.clear();
	m_offsetVector.push_back(0);
}
