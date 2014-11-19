// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsModelSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        MyPinDetailsModelSelectedMessage::MyPinDetailsModelSelectedMessage(const MyPins::MyPinModel& model)
        : m_model(model)
        {
            
        }
            
        const MyPins::MyPinModel& MyPinDetailsModelSelectedMessage::GetModel() const
        {
            return m_model;
        }
    }
}