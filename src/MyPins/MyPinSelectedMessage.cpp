// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectedMessage.h"


namespace ExampleApp
{
    namespace MyPins
    {
        MyPinSelectedMessage::MyPinSelectedMessage(const SdkModel::MyPinModel& myPinModel)
            : m_myPinModel(myPinModel)
        {

        }

        const SdkModel::MyPinModel& MyPinSelectedMessage::Model() const
        {
            return m_myPinModel;
        }
    }
}
