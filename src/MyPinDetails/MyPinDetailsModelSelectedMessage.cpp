// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModelSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        MyPinDetailsModelSelectedMessage::MyPinDetailsModelSelectedMessage(const MyPins::SdkModel::MyPinModel& model)
            : m_model(model)
        {

        }

        const MyPins::SdkModel::MyPinModel& MyPinDetailsModelSelectedMessage::GetModel() const
        {
            return m_model;
        }
    }
}
