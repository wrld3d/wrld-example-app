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
                
                InteriorVisibilityUpdater(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                          float interiorTransitionTimeSeconds);
                ~InteriorVisibilityUpdater();
                
                void SetInteriorShouldDisplay(bool shouldDisplay);
                const bool GetInteriorShouldDisplay() const;
                
                void SetInteriorTransitionParam(float param);
                const float GetInteriorTransitionParam() const;
                
                void Update(float dt);
                
            private:
                
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                float m_interiorTransitionParameter;
                float m_interiorTransitionTimeSeconds;
                bool m_interiorShouldDisplay;
                
            };
        }
    }
}
