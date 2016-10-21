// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Interiors.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace InteriorNavigationHelpers
        {
            bool IsPositionInInterior(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                       Eegeo::Location::ILocationService& locationService);
        }
    }
}
