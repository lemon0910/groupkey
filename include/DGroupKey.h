#ifndef DGROUPKEY_H
#define DGROUPKEY_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>

#include <BitCompressedVector.h>
#include <Dictionary.h>
#include <IndexOffset.h>
#include <RWMutex.h>
#include <Logging.h>

template <typename T>
struct RawData
{
    T data;
    uint64_t rownumber;

    bool operator<(const RawData b) const
    {
        if(data != b.data)
            return data < b.data;
        return rownumber < b.rownumber;
    }
};

template <typename T>
class DGroupKey
{
    typedef boost::shared_ptr<std::vector<uint64_t> > vectorptr;

public:
    DGroupKey(std::string columnName, uint64_t rowCount, uint64_t base, size_t type)
                :m_columnName(columnName) , m_base(base) , m_type(type)
    {
        m_dictionary = new Dictionary<T>;
        m_offset = new IndexOffset;
        m_position = new BitCompressedVector(rowCount);
    }

    DGroupKey(std::string columnName , uint64_t base , size_t type)
                :m_columnName(columnName) , m_base(base) , m_type(type)
    {
        m_dictionary = NULL;
        m_offset = NULL;
        m_position = NULL;
    }

    virtual ~DGroupKey()
    {
        delete m_dictionary;
        delete m_offset;
        delete m_position;
    }

    void constructThreeVector(std::vector<RawData<T> >& rawData)
    {
        std::sort(rawData.begin(), rawData.end());
        m_offset->push_back(0);
        uint64_t i = 0;
        for(auto itr = rawData.begin() ; itr != rawData.end() ; )
        {
            T value = itr->data;
            m_dictionary->push_back(value);
            auto iter = itr;
            while(iter->data == value)
            {
                m_position->push_back(iter->rownumber);
                i++;
                iter++;
            }
            m_offset->push_back(i);
            itr = iter;
        }
    }

    void constructThreeVector(Dictionary<T>* dict , IndexOffset* offsetVec,
                              BitCompressedVector* positionVec)
    {
        m_dictionary = dict;
        m_offset = offsetVec;
        m_position = positionVec;
    }

    vectorptr insertUpdatedData(Dictionary<T>* otherDictionary ,
                    IndexOffset* otherOffset , BitCompressedVector* otherPosition)
    {
        RWMutexLockGuard tmpLock(_mutex , WRITE);
        vectorptr xVector(new std::vector<uint64_t>); //for return

        Dictionary<T> tmpDictionary;
        IndexOffset tmpOffset;
        tmpOffset.push_back(0);
        uint64_t newRows = otherPosition->getRows();
        if(m_position == NULL)
        {
            //?
            vectorptr tmp;
            return tmp;
        }
        uint64_t totalRows = newRows + m_position->getRows();
        BitCompressedVector tmpPosition(totalRows);

        uint64_t m_dicPos = 0;
        uint64_t a_dicPos = 0;
        uint64_t n_dicPos = 0;
        uint64_t m_dicSize = m_dictionary->getRows();
        uint64_t a_dicSize = otherDictionary->getRows();

        while(m_dicPos < m_dicSize && a_dicPos < a_dicSize)
        {
            if(m_dictionary->get(m_dicPos) > otherDictionary->get(a_dicPos))
            {
                uint64_t thisOffset = otherOffset->get(a_dicPos + 1) -
                                otherOffset->get(a_dicPos);
                T thisDic = otherDictionary->get(a_dicPos);
                tmpDictionary.push_back(thisDic);
                tmpOffset.push_back(tmpOffset.get(n_dicPos) + thisOffset);
                for(uint64_t i = 0; i < thisOffset; i++)
                {
                    tmpPosition.push_back(
                        otherPosition->get(
                        otherOffset->get(a_dicPos) + i) + m_position->getRows());
                }
                a_dicPos++;
                n_dicPos++;
            }
            else if(m_dictionary->get(m_dicPos) < otherDictionary->get(a_dicPos))
            {
                uint64_t thisOffset = m_offset->get(m_dicPos + 1) - m_offset->get(m_dicPos);
                T thisDic = m_dictionary->get(m_dicPos);
                tmpDictionary.push_back(thisDic);
                tmpOffset.push_back(tmpOffset.get(n_dicPos) + thisOffset);
                for(uint64_t i = 0; i < thisOffset; i++)
                {
                    tmpPosition.push_back(m_position->get(m_offset->get(m_dicPos) + i));
                }
                xVector.push_back(n_dicPos - m_dicPos);
                m_dicPos++;
                n_dicPos++;
            }
            else
            {
                uint64_t thisOffset1 = m_offset->get(m_dicPos + 1) - m_offset->get(m_dicPos);
                uint64_t thisOffset2 = otherOffset->get(a_dicPos + 1) - otherOffset->get(a_dicPos);

                T thisDic = otherDictionary->get(a_dicPos);

                tmpDictionary.push_back(thisDic);
                tmpOffset.push_back(tmpOffset.get(n_dicPos) + thisOffset1 + thisOffset2);
                for(uint64_t i = 0; i < thisOffset1; i++)
                {
                    tmpPosition.push_back(m_position->get(m_offset->get(m_dicPos) + i));
                }
                for(uint64_t i = 0; i < thisOffset2; i++)
                {
                    tmpPosition.push_back(otherPosition->get(
                        otherOffset->get(a_dicPos) + i) + m_position->getRows());
                }
                xVector.push_back(n_dicPos - m_dicPos);
                m_dicPos++;
                a_dicPos++;
                n_dicPos++;
            }
        }

        if(m_dicPos < m_dicSize)
        {
            for(uint64_t i = m_dicPos; i < m_dicSize; i++)
            {
                uint64_t thisOffset = m_offset->get(m_dicPos + 1) - m_offset->get(m_dicPos);
                T thisDic = m_dictionary->get(m_dicPos);
                tmpDictionary.push_back(thisDic);
                tmpOffset.push_back(tmpOffset.get(n_dicPos) + thisOffset);
                for(uint64_t i = 0; i < thisOffset; i++)
                {
                    tmpPosition.push_back(m_position->get(m_offset->get(m_dicPos) + i));
                }
                xVector.push_back(n_dicPos - m_dicPos);
                m_dicPos++;
                n_dicPos++;
            }
        }
        else
        {
            for(uint64_t i = a_dicPos; i < a_dicSize; i++)
            {
                uint64_t thisOffset = otherOffset->get(a_dicPos + 1) - otherOffset->get(a_dicPos);
                T thisDic = otherDictionary->get(a_dicPos);
                tmpDictionary.push_back(thisDic);
                tmpOffset.push_back(tmpOffset.get(n_dicPos) + thisOffset);
                for(uint64_t i = 0; i < thisOffset; i++)
                {
                    tmpPosition.push_back(otherPosition->get(
                        otherOffset->get(a_dicPos) + i) + m_position->getRows());
                }
                a_dicPos++;
                n_dicPos++;
            }
        }

        m_dictionary->clear();
        m_offset->clear();
        m_position->resize(totalRows);
        m_position->clear();

        for(uint64_t i = 0; i <  n_dicPos; i++)
        {
            m_dictionary->push_back(tmpDictionary.get(i));
            m_offset->push_back(tmpOffset.get(i + 1));
        }
        for(uint64_t i = 0; i < totalRows; i++)
        {
            m_position->push_back(tmpPosition.get(i));
        }

        return xVector;
    }

    bool ifSplit()
    {
        return m_position->checkCapacity();
    }

    //二分分裂用于增量流程中的分裂，原则是留下前半部分的，将后半部分的联合索引返回给分裂函数的调用者
    DGroupKey<T>* binarysplit()
    {
        //remainCount表示前半部分的
        uint64_t remainCount = m_position->getRows() / 2;
        uint64_t itemCount;
        if(m_position->getRows() % 2 == 0)
            itemCount = remainCount;
        else
            itemCount = remainCount + 1;
        switch(m_type)
        {
        case 0:{
                   //base会改变了，原来的基础上加上前半截的数据量
                   DGroupKey<string>* newDGroupKey = new DGroupKey(
                       m_columnName, itemCount, m_base + remainCount, 0);
                   //创建三个向量的截半向量,从右往左的生成
                   size_t pos = remainCount;
                   while(pos < m_position->getRows())
                   {
                       newDGroupKey->m_position->push_back(m_position->get(pos));
                       pos++;
                   }
                   //生成IndexOffset,这一段理解的最好方式是举个例子，offsetPos表示的是IndexOffset的下标，而remainCount是具体的Positon向量中的值，二者的关系有点绕，要理清楚
                   uint64_t offsetPos = m_offset->findBinarySplitPos(remainCount);
                   uint64_t dicPos = offsetPos - 1;
                   while(offsetPos < m_offset->getRows())
                   {
                       newDGroupKey->m_offset->push_back(m_offset->get(offsetPos) - remainCount);
                       offsetPos++;
                   }
                   //生成Dictionary，同上需要仔细理解，主要是处理好对应关系
                   while(dicPos < m_dictionary->getRows())
                   {
                       newDGroupKey->m_dictionary->push_back(m_dictionary->get(dicPos));
                       dicPos++;
                   }
                   binaryShrink();
                   return newDGroupKey;
               }
        case 1:{
                   DGroupKey<int>* newDGroupKey = new DGroupKey(m_columnName, itemCount, m_base + remainCount, 1);
                   //创建三个向量的截半向量,从右往左的生成
                   size_t pos = remainCount;
                   while(pos < m_position->getRows())
                   {
                       newDGroupKey->m_position->push_back(m_position->get(pos));
                       pos++;
                   }
                   //生成IndexOffset,这一段理解的最好方式是举个例子，offsetPos表示的是IndexOffset的下标，而remainCount是具体的Positon向量中的值，二者的关系有点绕，要理清楚
                   uint64_t offsetPos = m_offset->findBinarySplitPos(remainCount);
                   uint64_t dicPos = offsetPos - 1;
                   while(offsetPos < m_offset->getRows())
                   {
                       newDGroupKey->m_offset->push_back(m_offset->get(offsetPos) - remainCount);
                       offsetPos++;
                   }
                   //生成Dictionary，同上需要仔细理解，主要是处理好对应关系
                   while(dicPos < m_dictionary->getRows())
                   {
                       newDGroupKey->m_dictionary->push_back(m_dictionary->get(dicPos));
                       dicPos++;
                   }
                   binaryShrink();
                   return newDGroupKey;
               }
        case 2:{
                   DGroupKey<double>* newDGroupKey =
                       new DGroupKey(m_columnName, itemCount, m_base + remainCount, 2);
                   //创建三个向量的截半向量,从右往左的生成
                   size_t pos = remainCount;
                   while(pos < m_position->getRows())
                   {
                       newDGroupKey->m_position->push_back(m_position->get(pos));
                       pos++;
                   }
                   //生成IndexOffset,这一段理解的最好方式是举个例子，offsetPos表示的是IndexOffset的下标，而remainCount是具体的Positon向量中的值，二者的关系有点绕，要理清楚
                   uint64_t offsetPos = m_offset->findBinarySplitPos(remainCount);
                   uint64_t dicPos = offsetPos - 1;
                   while(offsetPos < m_offset->getRows())
                   {
                       newDGroupKey->m_offset->push_back(m_offset->get(offsetPos) - remainCount);
                       offsetPos++;
                   }
                   //生成Dictionary，同上需要仔细理解，主要是处理好对应关系
                   while(dicPos < m_dictionary->getRows())
                   {
                       newDGroupKey->m_dictionary->push_back(m_dictionary->get(dicPos));
                       dicPos++;
                   }
                   binaryShrink();
                   return newDGroupKey;
               }
        }
    }

    //vector不太好压缩，真要做的好，还是要自己实现一个vector数组。
    void binaryShrink()
    {
        uint64_t remainCount = m_position->getRows() / 2;
        uint64_t offsetPos = m_offset->findBinarySplitPos(remainCount);
        m_position->posShrink(remainCount);
        m_offset->offsetShrink(offsetPos, remainCount);
        m_dictionary->dicShrink(offsetPos);

    }

    Dictionary<T>* getDictionary(){return m_dictionary;}
    IndexOffset* getOffset(){return m_offset;}
    BitCompressedVector* getPosition(){return m_position;}

    void print()
    {
        cout << "====Dictionary====" << endl;
        m_dictionary->print();
        cout << "==================" << endl;
        cout << "======Offset======" << endl;
        m_offset->print();
        cout << "==================" << endl;
        cout << "=====Position=====" << endl;
        m_position->print();
        cout << "==================" << endl;
    }

    string getName()
    {
        return m_columnName;
    }
    uint64_t getBase()
    {
        return m_base;
    }

    vector<uint64_t> getRangeRowKeyByPos(uint64_t floor, uint64_t ceiling)
    {
        vector<uint64_t> result;
        uint64_t offsetFloorPos = m_offset->get(floor);
        uint64_t offsetCeilingPos = m_offset->get(ceiling + 1); // need to plus 1
        for(uint64_t i = offsetFloorPos; i < offsetCeilingPos; i++)
        {
            result.push_back(m_position->get(i));
        }
        return result;
    }

    vector<uint64_t> getRowKeyByPos(uint64_t pos)
    {
        return getRangeRowKeyByPos(pos, pos);
    }

    vector<uint64_t> getRangeRowKeyById(uint64_t floor, uint64_t ceiling)
    {
        floor = floor - m_base;
        ceiling = ceiling - m_base;
        vector<uint64_t> result;
        uint64_t offsetFloorPos = m_offset->get(floor);
        uint64_t offsetCeilingPos = m_offset->get(ceiling + 1);
        for(uint64_t i = offsetFloorPos; i < offsetCeilingPos; i++)
        {
            result.push_back(m_position->get(i));
        }
        return result;
    }

    vector<uint64_t> getRowKeyById(uint64_t id)
    {
        return getRangeRowKeyById(id, id);
    }

    vector<T> getDicValue(vector<uint64_t> dicId)
    {
        vector<T> result;
        for(vector<uint64_t>::iterator itr = dicId.begin(); itr != dicId.end(); itr++)
            result.push_back(m_dictionary->get(*itr - m_base));
        return result;
    }

private:

    std::string m_columnName;
    uint64_t m_base;//dictionary base, because search is start from dictionary
    size_t m_type;
    BitCompressedVector* m_position;
    Dictionary<T>* m_dictionary;
    IndexOffset* m_offset;
    RWMutexLock _mutex;
};

#endif
