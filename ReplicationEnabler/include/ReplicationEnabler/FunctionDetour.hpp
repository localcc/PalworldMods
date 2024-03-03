#pragma once
#include <ReplicationEnabler/Function.hpp>

struct TFunctionDetour : IFunction_OwnedObject
{
    TFunctionDetour(void* DstFunctionPtr) : DstFunctionPtr(DstFunctionPtr)
    {
    }
    
    void* CloneToEmptyStorage(void* Storage) const override
    {
        *static_cast<void**>(Storage) = DstFunctionPtr;
        return Storage;
    }

    void* GetAddress() override
    {
        return DstFunctionPtr;
    }

    void Destroy() override
    {
    }

    ~TFunctionDetour() override
    {
    }

public:
    void* DstFunctionPtr;
};

template <typename T>
void DetourFunction(TFunction<T>& Function, void* DstFunctionPtr)
{
    Function.TempFuncPtr = DstFunctionPtr;
    Function.TempStorage.HeapAllocation = new TFunctionDetour(DstFunctionPtr);
}
