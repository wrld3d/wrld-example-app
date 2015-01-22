// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinRemovedFromMenuMessage::MyPinRemovedFromMenuMessage(SdkModel::MyPinModel* myPinModel)
            : m_pMyPinModel(myPinModel)
        {

        }

        SdkModel::MyPinModel* MyPinRemovedFromMenuMessage::GetMyPinModel() const
        {
            return m_pMyPinModel;
        }
    }
}
