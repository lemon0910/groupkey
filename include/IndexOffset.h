#ifndef INDEXOFFSET_H_
#define INDEXOFFSET_H_

#include <stdint.h>
#include <vector>

class IndexOffset{
	public:
		IndexOffset();
		virtual ~IndexOffset();
	    void push_back(uint64_t index);
		void print();
		uint64_t get(uint64_t pos);
		uint64_t getRows();
		uint64_t findBinarySplitPos(uint64_t positionIndex);
		void offsetShrink(uint64_t pos, uint64_t count);
		void clear();
	private:
        std::vector<uint64_t> m_offsetVector;
};

#endif
