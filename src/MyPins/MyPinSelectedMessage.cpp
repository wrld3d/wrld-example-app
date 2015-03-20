// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {   
        MyPinSelectedMessage::MyPinSelectedMessage(SdkModel::MyPinModel::TPinIdType pinId,
                             const Eegeo::Space::LatLong& pinLocation)
        : m_pinId(pinId)
        , m_pinLocation(pinLocation)
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
    }
}
