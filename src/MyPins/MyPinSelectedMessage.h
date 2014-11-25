// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectedMessage
        {
            const MyPinModel& m_myPinModel;
            
        public:
            MyPinSelectedMessage(const MyPinModel& myPinModel);
            
            const MyPinModel& Model() const;
        };
    }
}
