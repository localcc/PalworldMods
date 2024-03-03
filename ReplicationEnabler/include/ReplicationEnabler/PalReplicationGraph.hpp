#pragma once
#include <Unreal/UClass.hpp>

#include <ReplicationEnabler/Function.hpp>
#include <ReplicationEnabler/EClassRepNodeMapping.hpp>

template <typename Value>
struct TClassMap
{
    ::TFunction<bool(RC::Unreal::UClass**, Value&)> InitNewElement;
};

struct UPalReplicationGraph
{
    RC::Unreal::uint8 pad_0000[0x600];
    TClassMap<EClassRepNodeMapping> ClassRepNodePolicies;
};
