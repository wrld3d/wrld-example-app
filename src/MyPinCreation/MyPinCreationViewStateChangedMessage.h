// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationViewStateChangedMessage
        {
        public:
            MyPinCreationViewStateChangedMessage(MyPinCreationStage stage);

            const MyPinCreationStage& GetMyPinCreationStage() const;

        private:
            MyPinCreationStage m_stage;
        };
    }
}
