// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"
#include "Space.h"
#include "VectorMath.h"
#include "Types.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class IMyPinsService
        {
        public:
            virtual ~IMyPinsService() {}
            
            virtual void RemovePin(MyPinModel* myPinModel) = 0;
            
            virtual void SavePin(const std::string& title,
                                 const std::string& description,
                                 const Eegeo::Space::LatLong& latLong,
                                 Byte* imageData,
                                 size_t imageSize,
                                 bool shouldShare) = 0;
        };
    }
}