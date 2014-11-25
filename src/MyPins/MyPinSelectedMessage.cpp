// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinSelectedMessage.h"


namespace ExampleApp
{
    namespace MyPins
    {
        MyPinSelectedMessage::MyPinSelectedMessage(const MyPinModel& myPinModel)
        : m_myPinModel(myPinModel)
        {
            
        }
            
        const MyPinModel& MyPinSelectedMessage::Model() const
        {
            return m_myPinModel;
        }
    }
}
