// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinAddedToMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinAddedToMenuMessage::MyPinAddedToMenuMessage(SdkModel::MyPinModel* myPinModel)
            : m_pMyPinModel(myPinModel)
        {

        }

        SdkModel::MyPinModel* MyPinAddedToMenuMessage::GetMyPinModel() const
        {
            return m_pMyPinModel;
        }
    }
}
