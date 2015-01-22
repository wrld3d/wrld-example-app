// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "WorldPinItemModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsRepository : public Repository::IRepositoryModel<WorldPinItemModel*>
            {
            };
        }
    }
}
