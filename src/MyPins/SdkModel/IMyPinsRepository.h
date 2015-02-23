// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinsRepository : public Repository::IRepositoryModel<MyPinModel*>
            {

            };
        }
    }
}
