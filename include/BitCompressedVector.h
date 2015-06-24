#ifndef BITCOMPRESSEDVECTOR_H
#define BITCOMPRESSEDVECTOR_H

#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <Logging.h>

class BitCompressedVector
{
private:

    typedef uint64_t type_name_t;
    typedef uint64_t storage_unit_t;
    const static uint64_t bitWidth = sizeof(storage_unit_t) * 8;

public:

    BitCompressedVector(uint64_t rowCount);
    BitCompressedVector(const BitCompressedVector& other);
    BitCompressedVector& operator=(const BitCompressedVector& other);
    virtual ~BitCompressedVector();
    bool checkSize(uint64_t newRows);//before insertion, check, if resize
    void resize(uint64_t newRows);
    void shrinkSize(uint64_t newRows);
    void clear();
    void reset();
    void resetBitForItem(uint64_t value);
    void set(uint64_t rowID, uint64_t value);
    void push_back(uint64_t value);
    uint64_t get(uint64_t rowID);
    vector<uint64_t> getRange(uint64_t rowIDUpper, uint64_t rowIDLower);
    uint64_t getSize();
    uint64_t getRows();
    void posShrink(uint64_t pos);
    void print();

private:

    inline storage_unit_t* allocMemory(uint64_t blockNumber)
    {
        storage_unit_t* data = (storage_unit_t*)malloc(blockNumber * sizeof(storage_unit_t));
        if(data != NULL)
        {
            memset(data, 0, blockNumber * sizeof(storage_unit_t));
            return data;
        }
        else
        {
            LOG_INFO << "BitCompressedVector::allocMemory(uint64_t blockNumber) error";
            return NULL;
        }
    }

    inline uint64_t blockPosition(uint64_t rowID) const{
        return (m_bitForItem * rowID) / bitWidth;
    }

    inline uint64_t blockOffset(uint64_t rowID) const{
        return (m_bitForItem * rowID) % bitWidth;
    }

private:

    storage_unit_t* m_pData;
    uint64_t m_bitForItem;
    uint64_t m_size;
    uint64_t m_rowCount;
    uint64_t m_currentRow;
    uint64_t m_blockNumber;
};
#endif
