// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorVisibilityUpdater : private Eegeo::NonCopyable
            {
            public:
                
                InteriorVisibilityUpdater(Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                          const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          float interiorTransitionTimeSeconds);
                ~InteriorVisibilityUpdater();
                
                void SetInteriorShouldDisplay(bool shouldDisplay);
                
                void Update(float dt);
                
            private:
                
                Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const float m_interiorTransitionTimeSeconds;
                
                float m_interiorTransitionParameter;
                bool m_interiorShouldDisplay;
                
            };
        }
    }
}
