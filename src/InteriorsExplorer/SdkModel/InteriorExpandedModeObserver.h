// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "WorldPins.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorExpandedModeObserver
            {
            public:
                
                InteriorExpandedModeObserver(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController);
                ~InteriorExpandedModeObserver();
                
                
            private:
                
                void OnInteractionStateChanged();
                void SetExpanded(bool expanded);
                
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                WorldPins::SdkModel::IWorldPinsScaleController& m_worldPinsScaleController;
                Eegeo::Helpers::TCallback0<InteriorExpandedModeObserver> m_interactionStateChangedCallback;
                
                bool m_expanded;
                int m_previouslyCachedVisibilityMask;
            };

        }
    }
}