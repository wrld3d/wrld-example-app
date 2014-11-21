// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinRemovedFromMenuMessage::MyPinRemovedFromMenuMessage(MyPinModel* myPinModel)
        : m_pMyPinModel(myPinModel)
        {
            
        }
            
        MyPinModel* MyPinRemovedFromMenuMessage::GetMyPinModel() const
        {
            return m_pMyPinModel;
        }
    }
}
