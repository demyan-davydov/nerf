#include "AnimationsController.h"

AnimationsController::~AnimationsController()
{
    clear();
}

bool AnimationsController::empty() const
{
    return mAnimations.empty();
}

void AnimationsController::process(long currTimeUs)
{
    for (int i = 0; i < mAnimations.size(); ++i)
    {
        const auto& item = mAnimations[i];

        if (currTimeUs >= item.startTime)
        {
            if (isExpired(currTimeUs, item))
            {
                // final execution
                item.animation->perform(item.duration, item.duration, item.totalRepeats - 1);
                //removeByIndex(i--);

                delete item.animation;
                mAnimations.erase(i--);
            }
            else 
            {
                const auto elapsed = currTimeUs - item.startTime;
                const auto animationTime = elapsed % item.duration;
                const auto repeatIndex = static_cast<int>(elapsed / item.duration);
                item.animation->perform(animationTime, item.duration, repeatIndex);
            }
        }
    }

    // cleanup
}

int AnimationsController::add(long startTimeUs, long durationMs, Animation* anim, int totalRepeats)
{
    return since(startTimeUs).add(durationMs, anim, totalRepeats).animId();
}

bool AnimationsController::remove(int animId)
{
    // linear search, yeah!

    for (int i = 0; i < mAnimations.size(); ++i)
    {
        if (mAnimations[i].animId == animId)
        {
            delete mAnimations[i].animation;
        }
    }

    struct HaveId
    {
        int animId;
        HaveId(int animId) : animId(animId) {}
        bool operator()(Item const& item) const { return item.animId == animId; }
    };

    mAnimations.eraseIf(HaveId(animId));

    return true;
}

void AnimationsController::clear()
{
    for (int i = 0; i < mAnimations.size(); ++i)
    {
        delete mAnimations[i].animation;
    }

    mAnimations.clear();
}

AnimationsController::Adder AnimationsController::since(long startTimeUs)
{
    return Adder(*this, startTimeUs, popNextId());
}

// -------------------------------------------------------------------------------------
// private methods

bool AnimationsController::invalidParameters(long startTime, long durationUs, Animation* anim, int totalRepeats) // static
{
    // note: totalRepeats < 0 is accepted and means 'infinite animation'
    return anim == nullptr || durationUs <= 0 || totalRepeats == 0;
}

bool AnimationsController::canAppend(long startTimeUs, long durationUs, Animation* anim, int totalRepeats) const
{
    return mAnimations.available() && !invalidParameters(startTimeUs, durationUs, anim, totalRepeats);
}

bool AnimationsController::isExpired(long currTime, long durationUs, long startTime, int totalRepeats) const
{
    if (totalRepeats >= 0) // is not infinite
    {
        const auto endTime = startTime + durationUs * totalRepeats;
        return currTime >= endTime;
    }

    return false;
}

bool AnimationsController::isExpired(long currTime, Item const& item) const
{
    return isExpired(currTime, item.duration, item.startTime, item.totalRepeats);
}

/*
// Assumes the index is valid
void AnimationsController::removeByIndex(int idx)
{
    delete mAnimations[idx].animation;

    --mAnimationsSize;

    if (idx != mAnimationsSize) // is not the last element
    {
        // move last element instead removed
        mAnimations[idx] = mAnimations[mAnimationsSize];
    }
}
*/

int AnimationsController::popNextId()
{
    auto aId = mLastId++;
    if (aId == InvalidId)
    {
        aId = mLastId++;
    }

    return aId;
}

bool AnimationsController::addWithId(int animId, long startTimeUs, long durationUs, Animation* animation, int totalRepeats)
{
    if (!canAppend(startTimeUs, durationUs, animation, totalRepeats))
    {
        delete animation;
        return false;
    }

    /*auto& item = mAnimations[mAnimationsSize++];

    item.animId = animId;
    item.duration = durationUs;
    item.startTime = startTimeUs;
    item.totalRepeats = totalRepeats;
    item.animation = animation;
    */

    Item item;
    item.animId = animId;
    item.duration = durationUs;
    item.startTime = startTimeUs;
    item.totalRepeats = totalRepeats;
    item.animation = animation;

    mAnimations.push_back(item);

    return true;
}


// -------------------------------------------------------------------------------------
// AnimationsController::Adder 

AnimationsController::Adder& AnimationsController::Adder::add(long durationMs, Animation* anim, int totalRepeats)
{
    const long durationUs = durationMs * 1000;

    if (ctrl.addWithId(bulkAnimId, nextTimeUs, durationUs, anim, totalRepeats))
    {
        if (totalRepeats > 0) // if is not infinite animation
        {
            nextTimeUs += durationUs * totalRepeats;
        }
    }
    else 
    {
        bulkAnimId = InvalidId;
    }

    return *this;
}

AnimationsController::Adder& AnimationsController::Adder::pause(long durationMs)
{
    return *this;
}

int AnimationsController::Adder::animId() const
{
    return bulkAnimId;
}

