// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewPositionAnimator.h"

#include <Types.h>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewPositionAnimator::ViewPositionAnimator(UIView* view,
                                                       const Eegeo::v2& targetPosition,
                                                       double animationPeriodSeconds,
                                                       Curves::ICurve* curve,
                                                       OnAnimationComplete endCallback)
            : m_view(view)
            , m_startPosition(Eegeo::v2::Zero())
            , m_deltaPosition(Eegeo::v2::Zero())
            , m_targetPosition(targetPosition)
            , m_animationPeriodSeconds(animationPeriodSeconds)
            , m_curve(curve)
            , m_endCallback(endCallback)
            , m_isActive(false)
            , m_timer(0.0)
            {
                Eegeo_ASSERT(m_view != NULL, "Can't initialise ViewPositionAnimator with NULL view");
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewPositionAnimator with NULL curve");
            }
            
            ViewPositionAnimator::~ViewPositionAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewPositionAnimator::Play()
            {
                PlayWithNormalizedOffset(0.0f);
            }
            
            void ViewPositionAnimator::PlayWithNormalizedOffset(float offset)
            {
                Eegeo_ASSERT(offset >= 0.0f && offset <= 1.0f, "Normalized offset should be between one and zero (inclusive)");
                
                m_startPosition.x = m_view.frame.origin.x;
                m_startPosition.y = m_view.frame.origin.y;
                m_deltaPosition = m_targetPosition - m_startPosition;
                m_isActive = true;
                m_timer = offset * m_animationPeriodSeconds;
            }
            
            void ViewPositionAnimator::Update(double delta)
            {
                Eegeo_ASSERT(m_isActive, "Trying to update an inactive ViewPositionAnimator");
                
                m_timer = Eegeo::Min(m_timer + delta, m_animationPeriodSeconds);
                
                const Eegeo::v2& currentPositon = (*m_curve)((float)m_timer, m_startPosition, m_deltaPosition, (float)m_animationPeriodSeconds);
                
                CGRect frame = m_view.frame;
                frame.origin.x = currentPositon.x;
                frame.origin.y = currentPositon.y;
                m_view.frame = frame;
                
                if(m_timer == m_animationPeriodSeconds)
                {
                    m_isActive = false;
                    
                    if(m_endCallback != nil)
                    {
                        m_endCallback(m_view);
                    }
                }
            }
            
            bool ViewPositionAnimator::IsActive() const
            {
                return m_isActive;
            }
        }
    }
}
