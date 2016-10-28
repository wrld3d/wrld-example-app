// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        DirectionQueryResponseReceivedMessage::DirectionQueryResponseReceivedMessage(ExampleApp::Direction::SdkModel::DirectionResultModel& directionResultModel)
        : m_directionResultModel(directionResultModel)
        {
        }
        ExampleApp::Direction::SdkModel::DirectionResultModel& DirectionQueryResponseReceivedMessage::GetDirectionResultModel() const
        {
            return m_directionResultModel;
        }

        
    
    }
}