#pragma once

#include "utils.h"

#include <stdlib.h>

template<typename Item, int kMaxSize>
class SimpleArray final
{
    enum { kAlignment = 4 };
    enum { kItemAlignedSize = ((sizeof(Item) + kAlignment - 1) / kAlignment) * kAlignment };

public:
    SimpleArray()
    {
    }

    ~SimpleArray()
    {
        clear();
    }

    SimpleArray(SimpleArray const& other)
    {
        for (int i = 0; i < other.mSize; ++i)
        {
            new (pItem(mSize++)) Item(other[i]);
        }
    }

    SimpleArray& operator=(SimpleArray const& other)
    {
        if (this != &other)
        {
            clear();

            for (int i = 0; i < other.mSize; ++i)
            {
                new (pItem(mSize++)) Item(other[i]);
            }
        }

        return *this;
    }

    //! @returns true if nave no scheduled animations
    bool empty() const
    {
        return mSize == 0;
    }

    int size() const 
    {
        return mSize;
    }

    int available() const 
    {
        return kMaxSize - mSize;
    }

    void clear()
    {
        for (int i = 0; i < mSize; ++i)
        {
            pItem(i)->~Item();
        }

        mSize = 0;
    }

    //! 
    bool push_back(const Item& item)
    {
        if (available())
        {
            new (pItem(mSize++)) Item{item};
            //Item* p = new (pItem(mSize++)) Item;
            //*p = item;

            return true;
        }

        return false;
    }

    void erase(int index)
    {
        if (index >=0 && index < mSize)
        {
            for (int i = index + 1; i < mSize; ++i)
            {
                *pItem(i-1) = *pItem(i);
            }

            pItem(--mSize)->~Item();
        }
    }

    //! @brief Erases the specified element and moves the tail element to the location of the deleted
    void eraseInplace(int index)
    {
        if (index >=0 && index < mSize)
        {
            if (index + 1 != mSize) // not last
            {
                *pItem(index) = *pItem(mSize-1);
            }

            pItem(--mSize)->~Item();
        }
    }

    template<typename TFnObj>
    void eraseIf(TFnObj const& fnObj)
    {
        int i = 0; // destination index
        for (; i < mSize; ++i)
        {
            if (fnObj(*pItem(i)))
                break;
        }

        for (int j = i + 1; j < mSize; ++j)
        {
            if (fnObj(*pItem(j)))
                continue;

            *pItem(i++) = *pItem(j);
        }

        const int newSize = i;

        // call d'tor for removed elements
        for (; i < mSize; ++i)
        {
            pItem(i)->~Item();
        }

        mSize = newSize;
    }

    Item& operator[](int index) { return *pItem(index); }
    Item const& operator[](int index) const { return *pItem(index); }

    Item* begin() { return reinterpret_cast<Item*>(mData); }
    Item* end() { return pItem(mSize); }

    Item const* cbegin() const { return reinterpret_cast<Item const*>(mData); }
    Item const* cend() const { return pItem(mSize); }

    Item const* begin() const { return cbegin(); }
    Item const* end() const { return cend(); }

    Item& front() { return *begin(); }
    Item const& front() const { return *begin(); }

    Item& back() { return *pItem(mSize-1); }
    Item const& back() const { return *pItem(mSize-1); }


    //typedef int (*SortFn)(const Item&, const Item&);
    typedef int (*SortFn)(const void* item1, const void* item2);

    void sort(SortFn sortFn)
    {
        ::qsort(mData, mSize, kItemAlignedSize, sortFn);
    }

private:
    Item*       pItem(int idx)       { return reinterpret_cast<Item*>(&mData[idx * kItemAlignedSize]); }
    Item const* pItem(int idx) const { return reinterpret_cast<Item const*>(&mData[idx * kItemAlignedSize]); }

private:
    char mData[kMaxSize * kItemAlignedSize];
    int mSize = 0;
};
