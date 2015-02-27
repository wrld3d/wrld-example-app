// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinBoundObjectRepository
            {
            public:
                virtual ~IMyPinBoundObjectRepository() { }
                
                virtual void AddBoundItemForPin(MyPinModel::TPinIdType pinId, IMyPinBoundObject& item) = 0;
                
                virtual void RemoveBoundItemForPin(MyPinModel::TPinIdType pinId) = 0;
                
                virtual IMyPinBoundObject& GetBoundObjectForPin(const MyPinModel& pin) = 0;
            };
        }
    }
}
