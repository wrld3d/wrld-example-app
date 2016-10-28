// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <vector>
#include "SearchQuery.h"
#include "SearchResultModel.h"
#include "DirectionResultModel.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        class DirectionQueryResponseReceivedMessage
        {
        private:
            ExampleApp::Direction::SdkModel::DirectionResultModel& m_directionResultModel;
        public:
            DirectionQueryResponseReceivedMessage(ExampleApp::Direction::SdkModel::DirectionResultModel& directionResultModel);
            ExampleApp::Direction::SdkModel::DirectionResultModel& GetDirectionResultModel() const;
            

            
        };
    }
}
