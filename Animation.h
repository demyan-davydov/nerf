#pragma once

#include "types.h"

class Animation
{
public:
    virtual ~Animation() = default;

    virtual void perform(long currTime, long totalTime, int repeatCount) const = 0;
};

/*
template <uint First, uint ...Least>
class CompoundAnimation
{
public:
    enum { size = 1 + sizeof...(Least) };

    enum : uint { summ = First + CompoundAnimation<Least...>::summ };

private: 
    template <int N, int SFirst, int ...SLeast>
    struct PartialSumm
    {
         enum { value = SFirst + PartialSumm<N-1, SLeast...>::value };
    };
    
    template <int SFirst, int ...SLeast>
    struct PartialSumm<1, SFirst, SLeast...>
    {
         enum { value = SFirst };
    };

    template <int SFirst, int ...SLeast>
    struct PartialSumm<0, SFirst, SLeast...>
    {
         enum { value = 0 };
    };
    
public:
    template <int N>
    struct SummN
    {
        enum { value = PartialSumm<N, First, Least...>::value };
    };

    template <uint N>
    struct Range
    {
        enum { begin = SummN<N>::value,
               end = SummN<N+1>::value };
    };

public:

    inline int subanimation(long currTime, long fullTime, long& subCurrTime, long subFullTime)
    {

    }
};

template <uint First>
class CompoundAnimation<First>
{
public:
    enum { size = 1 };

    enum { summ = First };

    template <int N, int SFirst, int ...SLeast>
    struct SummN
    {
        enum { value = First };
    };
};
*/

