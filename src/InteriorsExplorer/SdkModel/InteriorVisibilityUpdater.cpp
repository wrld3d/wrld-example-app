// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorVisibilityUpdater.h"
#include "MathFunc.h"
#include "InteriorController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorVisibilityUpdater::InteriorVisibilityUpdater(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                 float transitionDurationTimeSeconds)
            : m_interiorController(interiorController)
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
            
            const bool InteriorVisibilityUpdater::GetInteriorShouldDisplay() const
            {
                return m_interiorShouldDisplay;
            }
            
            void InteriorVisibilityUpdater::SetInteriorTransitionParam(float param)
            {
                m_interiorTransitionParameter = Eegeo::Math::Clamp01(param);
            }
            
            const float InteriorVisibilityUpdater::GetInteriorTransitionParam() const
            {
                return m_interiorTransitionParameter;
            }
            
            void InteriorVisibilityUpdater::Update(float dt)
            {
                if(!m_interiorController.InteriorInScene())
                {
                    m_interiorTransitionParameter = 0.0f;
                    return;
                }
                
                if(m_interiorShouldDisplay && m_interiorTransitionParameter < 1.0f)
                {
                    if(m_interiorTransitionTimeSeconds == 0.0f)
                    {
                        m_interiorTransitionParameter = 1.0f;
                    }
                    else
                    {
                        m_interiorTransitionParameter += dt/m_interiorTransitionTimeSeconds;
                    }
                }
                else if(!m_interiorShouldDisplay && m_interiorTransitionParameter > 0.0f)
                {
                    if(m_interiorTransitionTimeSeconds == 0.0f)
                    {
                        m_interiorTransitionParameter = 0.0f;
                    }
                    else
                    {
                        m_interiorTransitionParameter -= dt/m_interiorTransitionTimeSeconds;
                    }

                }
                
                m_interiorTransitionParameter = Eegeo::Math::Clamp01(m_interiorTransitionParameter);
                
                m_interiorController.SetExteriorToInteriorParam(m_interiorTransitionParameter);
            }
        }
    }
}