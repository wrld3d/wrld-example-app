// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationStateChangedMessage
        {
        public:
            MyPinCreationStateChangedMessage(MyPinCreationStage& stage)
            : m_stage(stage)
            {
                
            }
            
            const MyPinCreationStage& GetMyPinCreationStage() const
            {
                return m_stage;
            }
            
        private:
            MyPinCreationStage m_stage;
        };
    }
}