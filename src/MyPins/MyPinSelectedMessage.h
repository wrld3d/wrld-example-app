// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectedMessage
        {
            SdkModel::MyPinModel::TPinIdType m_pinId;
            Eegeo::Space::LatLong m_pinLocation;
            Eegeo::Resources::Interiors::InteriorId m_interiorId;
            int m_targetFloorIndex;
            
        public:
            MyPinSelectedMessage(SdkModel::MyPinModel::TPinIdType pinId,
                                 const Eegeo::Space::LatLong& pinLocation,
                                 const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                 int targetFloorIndex
                                 );
            
            SdkModel::MyPinModel::TPinIdType GetPinId() const;
            
            const Eegeo::Space::LatLong& GetPinLocation() const;
            
            const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const;
            
            const int GetFloorIndex() const;

        };
    }
}
