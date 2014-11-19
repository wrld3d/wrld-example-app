// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class MyPinDetailsModelSelectedMessage
        {
        private:
            MyPins::MyPinModel m_model;
            
        public:
            MyPinDetailsModelSelectedMessage(const MyPins::MyPinModel& model);
            
            const MyPins::MyPinModel& GetModel() const;
        };
    }
}
