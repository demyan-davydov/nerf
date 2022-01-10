#pragma once


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
            new (pItem(mSize++)) Item(item);
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

private:
    Item*       pItem(int idx)       { return reinterpret_cast<Item*>(mData[idx * kItemAlignedSize]); }
    Item const* pItem(int idx) const { return reinterpret_cast<Item const*>(mData[idx * kItemAlignedSize]); }

private:
    char mData[kMaxSize * kItemAlignedSize];
    int mSize = 0;
};
