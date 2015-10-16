// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"

#include "SwallowTransitionResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchTransitionPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                {
                public:
                    SwallowSearchTransitionPinSelectionHandler(const SwallowTransitionResultModel& transitionResult);
                    
                    void SelectPin();
                private:
                    SwallowTransitionResultModel m_transitionResult;
                };
            }
        }
    }
}