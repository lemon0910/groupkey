#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <vector>
#include <algorithm>
#include <Logging.h>

template <class T>
class Dictionary{
	private:
		typedef std::vector<T> vector_t;
	public:
		Dictionary(){}
		virtual ~Dictionary()
        {
            clear();
        }

	    void push_back(T value)
        {
            m_dicVector.push_back(value);
        }

		void print()
		{
			uint64_t i = 0;
			for(typename vector_t::iterator itr = m_dicVector.begin(); itr != m_dicVector.end(); itr++)
			{
				LOG_INFO << "Dictionary[" << i << "]: " << *itr;
				i++;
			}
		}

		T get(uint64_t pos)
        {
            if(pos >= getRows())
            {
                LOG_INFO << "out of Range";

            }

            return m_dicVector[pos];
        }

		uint64_t getRows()
        {
            return m_dicVector.size();
        }

		uint64_t getSurePos(T value)
		{
			auto itr = std::upper_bound(m_dicVector.begin(), m_dicVector.end(), value);
			uint64_t ret = distance(m_dicVector.begin(), itr);
            return ret - 1;
		}

		bool ifExist(T value)
		{
            return std::binary_search(m_dicVector.begin(), m_dicVector.end(), value);
		}

		int64_t letGetPos(T floor)
		{
			if(floor < m_dicVector[0])
				return -1;

            auto itr = std::upper_bound(m_dicVector.begin(),m_dicVector.end(), floor);
			return distance(m_dicVector.begin(), itr);
		}

		int64_t ltGetPos(T floor)
		{
			if(floor < m_dicVector[0])
				return -1;
			auto itr = lower_bound(m_dicVector.begin(), m_dicVector.end(), floor);
			return distance(m_dicVector.begin(), itr);
		}

		int64_t getGetPos(T ceiling)
		{
			if(ceiling > m_dicVector[m_dicVector.size() - 1])
				return -1;

			typename vector_t::iterator itr = lower_bound(m_dicVector.begin(), m_dicVector.end(), ceiling);
			return distance(m_dicVector.begin(), itr);
		}

		int64_t gtGetPos(T ceiling)
		{
			if(ceiling > m_dicVector[m_dicVector.size() - 1])
				return -1;
			typename vector_t::iterator itr = upper_bound(m_dicVector.begin(), m_dicVector.end(), ceiling);
			return distance(m_dicVector.begin(), itr);
		}

		void dicShrink(size_t pos)
		{
			for(typename vector_t::iterator itr = m_dicVector.begin() + pos; itr != m_dicVector.end();)
			{
				itr = m_dicVector.erase(itr);
			}
		}

		void clear()
        {
            m_dicVector.clear();
        }
	private:
		vector_t m_dicVector;
};
#endif
