// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinAddedToMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinAddedToMenuMessage::MyPinAddedToMenuMessage(SdkModel::MyPinModel::TPinIdType myPinId,
                                                         const std::string& myPinTitle,
                                                         const std::string& myPinIcon,
                                                         const Eegeo::Space::LatLong& myPinLocation,
                                                         const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                         int floorIndex)
            : m_myPinId(myPinId)
            , m_myPinTitle(myPinTitle)
            , m_myPinIcon(myPinIcon)
            , m_pinLocation(myPinLocation)
            , m_interiorId(interiorId)
            , m_floorIndex(floorIndex)
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
        
        const Eegeo::Resources::Interiors::InteriorId& MyPinAddedToMenuMessage::GetMyPinInteriorId() const
        {
            return m_interiorId;
        }
        
        const int MyPinAddedToMenuMessage::GetMyPinFloorIndex() const
        {
            return m_floorIndex;
        }
    }
}
