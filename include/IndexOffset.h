#ifndef INDEXOFFSET_H_
#define INDEXOFFSET_H_

#include <stdint.h>
#include <BitCompressedVector.h>

class IndexOffset{
	public:
		IndexOffset();
        IndexOffset(uint64_t n);
		virtual ~IndexOffset();
	    void push_back(uint64_t index);
		void print();
		uint64_t get(uint64_t pos);
		uint64_t getRows();
		//uint64_t findBinarySplitPos(uint64_t positionIndex);
		void offsetShrink(uint64_t pos, uint64_t count);
		void clear();
	private:
        BitCompressedVector m_offsetVector;
};

#endif
