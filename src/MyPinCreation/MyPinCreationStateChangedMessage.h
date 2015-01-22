// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationStateChangedMessage
        {
        public:
            MyPinCreationStateChangedMessage(MyPinCreationStage& stage);

            const MyPinCreationStage& GetMyPinCreationStage() const;

        private:
            MyPinCreationStage m_stage;
        };
    }
}
