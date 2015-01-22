// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationStateChangedMessage::MyPinCreationStateChangedMessage(MyPinCreationStage& stage)
            : m_stage(stage)
        {

        }

        const MyPinCreationStage& MyPinCreationStateChangedMessage::GetMyPinCreationStage() const
        {
            return m_stage;
        }
    }
}
