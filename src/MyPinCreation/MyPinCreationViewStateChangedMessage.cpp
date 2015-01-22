// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationViewStateChangedMessage::MyPinCreationViewStateChangedMessage(MyPinCreationStage stage)
            : m_stage(stage)
        {

        }

        const MyPinCreationStage& MyPinCreationViewStateChangedMessage::GetMyPinCreationStage() const
        {
            return m_stage;
        }
    }
}
