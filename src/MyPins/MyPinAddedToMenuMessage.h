// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPins.h"
#include "MyPinModel.h"

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
                                    const Eegeo::Space::LatLong& myPinLocation);
            
            SdkModel::MyPinModel::TPinIdType GetMyPinId() const;
            
            const std::string& GetMyPinTitle() const;
            
            const std::string& GetMyPinIcon() const;
            
            const Eegeo::Space::LatLong& GetMyPinLocation() const;
            
        private:
            
            SdkModel::MyPinModel::TPinIdType m_myPinId;
            std::string m_myPinIcon;
            std::string m_myPinTitle;
            Eegeo::Space::LatLong m_pinLocation;
        };
    }
}
