// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectedMessage.h"


namespace ExampleApp
{
    namespace MyPins
    {   
        MyPinSelectedMessage::MyPinSelectedMessage(SdkModel::MyPinModel::TPinIdType pinId,
                                                   const Eegeo::Space::LatLong& pinLocation,
                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                   int targetFloorIndex)
        : m_pinId(pinId)
        , m_pinLocation(pinLocation)
        , m_interiorId(interiorId)
        , m_targetFloorIndex(targetFloorIndex)
        {
            
        }
    
        SdkModel::MyPinModel::TPinIdType MyPinSelectedMessage::GetPinId() const
        {
            return m_pinId;
        }
        
        const Eegeo::Space::LatLong& MyPinSelectedMessage::GetPinLocation() const
        {
            return m_pinLocation;
        }
        
        const Eegeo::Resources::Interiors::InteriorId& MyPinSelectedMessage::GetInteriorId() const
        {
            return m_interiorId;
        }
        
        const int MyPinSelectedMessage::GetFloorIndex() const
        {
            return m_targetFloorIndex;
        }
    }
}
