// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinRemovedFromMenuMessage::MyPinRemovedFromMenuMessage(SdkModel::MyPinModel::TPinIdType myPinId)
            : m_myPinId(myPinId)
        {

        }

        SdkModel::MyPinModel::TPinIdType MyPinRemovedFromMenuMessage::GetMyPinId() const
        {
            return m_myPinId;
        }
    }
}
