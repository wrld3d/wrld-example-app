// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class MyPinDetailsViewRemovePinMessage
        {
        public:
            MyPinDetailsViewRemovePinMessage(const int myPinModelId);

            ~MyPinDetailsViewRemovePinMessage();

            int GetMyPinModelId() const;

        private:
            int m_myPinModelId;
        };
    }
}
