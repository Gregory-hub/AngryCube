#pragma once
#include "IDestructable.h"


class IDestructableContainer
{
public:
    virtual void AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed) = 0;

private:
    virtual void DestroyObjectsInQueue() = 0;
};

