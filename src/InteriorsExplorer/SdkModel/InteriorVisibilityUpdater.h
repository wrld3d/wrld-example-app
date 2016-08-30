// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include <memory>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorVisibilityUpdater : private Eegeo::NonCopyable
            {
            public:
                
                InteriorVisibilityUpdater(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel,
                                          const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                          const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel);
                ~InteriorVisibilityUpdater();
                
                void SetInteriorShouldDisplay(bool shouldDisplay);
                
                void Update(float dt);
                
            private:
                
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                const float m_interiorTransitionTimeSeconds;
                
                float m_interiorTransitionParameter;
                bool m_interiorShouldDisplay;
                
            };
        }
    }
}
