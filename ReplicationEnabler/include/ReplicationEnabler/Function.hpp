#pragma once
#include <Unreal/Function.hpp>

template <typename T>
struct TFunction
{
    void* TempFuncPtr;
    RC::Unreal::FFunctionStorage TempStorage;
};

/**
 * Common interface to a callable object owned by TFunction.
 */
struct IFunction_OwnedObject
{
    /**
     * Creates a copy of itself into the storage and returns a pointer to the new object within it.
     */
    virtual void* CloneToEmptyStorage(void* Storage) const = 0;

    /**
     * Returns the address of the object.
     */
    virtual void* GetAddress() = 0;

    /**
     * Destructor.
     */
    virtual void Destroy() = 0;

    /**
     * Destructor.
     */
    virtual ~IFunction_OwnedObject() = default;
};
