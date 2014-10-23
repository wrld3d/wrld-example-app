// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "WorldPinItemModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class IWorldPinsRepository : public Repository::IRepositoryModel<WorldPinItemModel>
        {
            
        };
    }
}
