#pragma once
#include <Unreal/Core/Hal/Platform.hpp>

enum class EClassRepNodeMapping : RC::Unreal::uint8
{
    NotRouted,
    RelevantAllConnections,
    Spatialize_Static,
    Spatialize_Dynamic,
    Spatialize_Dormancy,
};
