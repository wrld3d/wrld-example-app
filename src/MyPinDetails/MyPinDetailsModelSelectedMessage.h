// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class MyPinDetailsModelSelectedMessage
        {
        private:
            MyPins::SdkModel::MyPinModel m_model;

        public:
            MyPinDetailsModelSelectedMessage(const MyPins::SdkModel::MyPinModel& model);

            const MyPins::SdkModel::MyPinModel& GetModel() const;
        };
    }
}
