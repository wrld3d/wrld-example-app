// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinAddedToMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinAddedToMenuMessage::MyPinAddedToMenuMessage(SdkModel::MyPinModel::TPinIdType myPinId,
                                                         const std::string& myPinTitle,
                                                         const std::string& myPinIcon,
                                                         const Eegeo::Space::LatLong& myPinLocation)
            : m_myPinId(myPinId)
            , m_myPinTitle(myPinTitle)
            , m_myPinIcon(myPinIcon)
            , m_pinLocation(myPinLocation)
        {

        }
        
        SdkModel::MyPinModel::TPinIdType MyPinAddedToMenuMessage::GetMyPinId() const
        {
            return m_myPinId;
        }
        
        const std::string& MyPinAddedToMenuMessage::GetMyPinTitle() const
        {
            return m_myPinTitle;
        }
        
        const std::string& MyPinAddedToMenuMessage::GetMyPinIcon() const
        {
            return m_myPinIcon;
        }
        
        const Eegeo::Space::LatLong& MyPinAddedToMenuMessage::GetMyPinLocation() const
        {
            return m_pinLocation;
        }
    }
}
