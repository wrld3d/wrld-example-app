// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectedMessage
        {
            SdkModel::MyPinModel::TPinIdType m_pinId;
            Eegeo::Space::LatLong m_pinLocation;
            
        public:
            MyPinSelectedMessage(SdkModel::MyPinModel::TPinIdType pinId,
                                 const Eegeo::Space::LatLong& pinLocation);
            
            SdkModel::MyPinModel::TPinIdType GetPinId() const;
            
            const Eegeo::Space::LatLong& GetPinLocation() const;

        };
    }
}
