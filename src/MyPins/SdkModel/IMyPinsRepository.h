// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class IMyPinsRepository : public Repository::IRepositoryModel<MyPinModel*>
        {
            
        };
    }
}
