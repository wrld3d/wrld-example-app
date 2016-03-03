// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorVisibilityUpdater.h"
#include "MathFunc.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorVisibilityUpdater::InteriorVisibilityUpdater(Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 float transitionDurationTimeSeconds)
            : m_interiorTransitionModel(interiorTransitionModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorShouldDisplay(false)
            , m_interiorTransitionParameter(0.0f)
            , m_interiorTransitionTimeSeconds(Eegeo::Max(transitionDurationTimeSeconds, 0.0f))
            {
                
            }
            
            InteriorVisibilityUpdater::~InteriorVisibilityUpdater()
            {
                
            }
            
            void InteriorVisibilityUpdater::SetInteriorShouldDisplay(bool shouldDisplay)
            {
                m_interiorShouldDisplay = shouldDisplay;
            }
            
            void InteriorVisibilityUpdater::Update(float dt)
            {
                const bool shouldDisplay = m_interiorShouldDisplay && m_interiorSelectionModel.IsInteriorSelected() && m_interiorInteractionModel.HasInteriorModel();
                const float transitionTarget = shouldDisplay ? 1.f : 0.f;
                
                float delta = 0.f;
                if (m_interiorTransitionParameter < transitionTarget)
                {
                    delta = dt;
                }
                else if (m_interiorTransitionParameter > transitionTarget)
                {
                    delta = -dt;
                }
                
                m_interiorTransitionParameter += delta / m_interiorTransitionTimeSeconds;
                m_interiorTransitionParameter = Eegeo::Math::Clamp01(m_interiorTransitionParameter);
                
                m_interiorTransitionModel.SetVisibilityParam(m_interiorTransitionParameter);
            }
        }
    }
}