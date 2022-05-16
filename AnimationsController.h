#pragma once

#include "Animation.h"
#include "SimpleArray.h"

// Usage:
// AnimationsController animCtrl;
//
// // add one animation for 500 ms
// auto animId1 = animCtrl.add(micros(), 500, new MySuperAnimation(111));
// 
// // add 2 sequental animations with same Id
// auto animId2 = animCtrl.since(micros())
//                        .add(500, new MyUberAnimation(1))
//                        .pause(100)
//                        .add(1000, new MyUberAnimation(2)).animId();
//
// // remove first animation
// animCtrl.remove(animId1);
//
// void loop()
// {
//     animCtrl.process(micros());
// }

class AnimationsController
{
    enum { kMaxAnimations = 8 };

public:
    enum { InvalidId = 0 };

    virtual ~AnimationsController();

    //! @returns true if nave no scheduled animations
    bool empty() const;

    //! @brief Handles all animations
    //! Automatically removes all expired animations
    void process(long currTimeUs);

    //! @brief Add one animation
    //! @returns AnimationId
    int add(long startTimeUs, long durationMs, Animation* anim, int totalRepeats = 1);

    //! @brief Removes all animations with specified 'animId'
    bool remove(int animId);

    //! @brief Removes all animations
    void clear();

    //! @brief Helper class for adding few animations
    struct Adder 
    {
    public:
        Adder& add(long durationMs, Animation* anim, int totalRepeats = 1);
        Adder& pause(long durationMs);
        int animId() const;

    private:
        friend class AnimationsController;

        Adder(AnimationsController& ctrl, long nextTimeUs, int bulkAnimId) 
        : ctrl(ctrl), nextTimeUs(nextTimeUs), bulkAnimId(bulkAnimId) 
        {}

    private:
        AnimationsController& ctrl;
        long nextTimeUs = 0;
        int bulkAnimId = InvalidId;
    };

    friend class Adder;

    //! @brief returns animations appender
    Adder since(long startTime);

private:
    struct Item
    {
        Item() = default;
        Item(Item const&) = default;
        Item& operator=(Item const&) = default;

        int animId = InvalidId; // non unique animation id
        long duration = 0; // nanoseconds 
        long startTime = 0; // nanoseconds
        int totalRepeats = 0; // -1 means infinite

        Animation* animation = nullptr;
    };

    static bool invalidParameters(long startTimeUs, long durationUs, Animation* anim, int totalRepeats);

    bool canAppend(long startTimeUs, long durationUs, Animation* anim, int totalRepeats) const;

    bool isExpired(long currTime, long durationUs, long startTime, int totalRepeats) const;

    bool isExpired(long currTime, Item const&) const;

    int popNextId();

    bool addWithId(int aId, long startTimeUs, long durationMs, Animation* anim, int totalRepeats);

private:
    SimpleArray<Item, kMaxAnimations> mAnimations;
    int mLastId = InvalidId; // Id (not unique) for animation
    int mLastOrder = 0;
};
