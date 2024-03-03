#include <Mod/CppUserModBase.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/Hooks.hpp>

#include <ReplicationEnabler/PalReplicationGraph.hpp>
#include <ReplicationEnabler/FunctionDetour.hpp>


using namespace RC;
using namespace RC::Unreal;

class ReplicationEnabler : public CppUserModBase
{
public:
    ReplicationEnabler()
    {
        ModName = STR("ReplicationEnabler");
        ModVersion = STR("1.0.0");
        ModDescription = STR("A mod that enables custom actor replication for palworld.");
        ModAuthors = STR("localcc, Yangff");

        Output::send(STR("[ReplicationEnabler] Hello world!\n"));
    }

    auto on_unreal_init() -> void override
    {
        const auto GraphClassName = STR("/Script/Pal.PalReplicationGraph");
        constexpr EObjectFlags RequiredFlags = RF_Transient;

        UClass* PalReplicationGraphClass = UObjectGlobals::StaticFindObject<UClass*>(
            nullptr, nullptr, STR("/Script/Pal.PalReplicationGraph"));

        RegisterOnGraphConstruct(PalReplicationGraphClass, RequiredFlags);

        const FName ClassName(GraphClassName, FNAME_Add);
        if (UObject* ReplicationGraph = UObjectGlobals::FindObject(ClassName, FName(), RequiredFlags))
        {
            OnFoundReplicationGraph(reinterpret_cast<UPalReplicationGraph*>(ReplicationGraph));
        }
    }

    static auto OnFoundReplicationGraph(UPalReplicationGraph* ReplicationGraph) -> void
    {
        DetourFunction(ReplicationGraph->ClassRepNodePolicies.InitNewElement, &InitNewElement);
    }

    static auto InitNewElement(void* Self, UClass** ClassPtr, uint32& Value)
    {
        UClass* Class = *ClassPtr;
        if (Class->GetFullName().contains(STR("/Game/Mods")))
        {
            UObject* CDO = Class->GetClassDefaultObject();
            const bool bReplicates = *CDO->GetValuePtrByPropertyNameInChain<bool>(STR("bReplicates"));
            const bool bAlwaysRelevant = *CDO->GetValuePtrByPropertyNameInChain<bool>(STR("bAlwaysRelevant"));

            if (!bReplicates)
            {
                Value = static_cast<uint32>(EClassRepNodeMapping::NotRouted);
                return true;
            }

            if (bAlwaysRelevant)
            {
                Value = static_cast<uint32>(EClassRepNodeMapping::RelevantAllConnections);
                return true;
            }

            Value = static_cast<uint32>(EClassRepNodeMapping::Spatialize_Dynamic);
            return true;
        }

        return false;
    }

    static auto RegisterOnGraphConstruct(UClass* PalReplicationGraphClass, EObjectFlags FlagsToCheck) -> void
    {
        Hook::RegisterStaticConstructObjectPostCallback(
            [PalReplicationGraphClass, FlagsToCheck](const FStaticConstructObjectParameters& Params,
                                                     UObject* ConstructedObject) -> UObject* {
                UStruct* ObjectClass = ConstructedObject->GetClassPrivate();
                while (ObjectClass)
                {
                    if (ObjectClass == PalReplicationGraphClass && ConstructedObject->HasAnyFlags(FlagsToCheck))
                    {
                        UPalReplicationGraph* ReplicationGraph = reinterpret_cast<UPalReplicationGraph*>(
                            ConstructedObject);
                        OnFoundReplicationGraph(ReplicationGraph);
                    }
                    ObjectClass = ObjectClass->GetSuperStruct();
                }

                return ConstructedObject;
            });
    }
};

#define REPLICATION_ENABLER_API __declspec(dllexport)

extern "C" {
REPLICATION_ENABLER_API CppUserModBase* start_mod()
{
    return new ReplicationEnabler();
}

REPLICATION_ENABLER_API void uninstall_mod(CppUserModBase* mod)
{
    delete mod;
}
}
