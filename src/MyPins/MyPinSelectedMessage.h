// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectedMessage
        {
            const SdkModel::MyPinModel& m_myPinModel;

        public:
            MyPinSelectedMessage(const SdkModel::MyPinModel& myPinModel);

            const SdkModel::MyPinModel& Model() const;
        };
    }
}
