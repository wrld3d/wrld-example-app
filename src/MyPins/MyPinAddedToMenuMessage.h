// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPins.h"
#include "MyPinModel.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinAddedToMenuMessage
        {
        public:
            MyPinAddedToMenuMessage(SdkModel::MyPinModel::TPinIdType myPinId,
                                    const std::string& myPinTitle,
                                    const std::string& myPinIcon,
                                    const Eegeo::Space::LatLong& myPinLocation,
                                    const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                    int floorIndex);
            
            SdkModel::MyPinModel::TPinIdType GetMyPinId() const;
            
            const std::string& GetMyPinTitle() const;
            
            const std::string& GetMyPinIcon() const;
            
            const Eegeo::Space::LatLong& GetMyPinLocation() const;
            
            const Eegeo::Resources::Interiors::InteriorId& GetMyPinInteriorId() const;
            
            const int GetMyPinFloorIndex() const;
            
        private:
            
            SdkModel::MyPinModel::TPinIdType m_myPinId;
            std::string m_myPinIcon;
            std::string m_myPinTitle;
            Eegeo::Space::LatLong m_pinLocation;
            Eegeo::Resources::Interiors::InteriorId m_interiorId;
            int m_floorIndex;
        };
    }
}
