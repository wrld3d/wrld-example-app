// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewPositionAnimator.h"

#include <cmath>
#include <Types.h>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewPositionAnimator::ViewPositionAnimator(UIView* view,
                                                       double animationPeriodSeconds,
                                                       double startDelaySeconds,
                                                       const Eegeo::v2& defaultStartPosition,
                                                       const Eegeo::v2& targetPosition,
                                                       Easing::IEasingCurve<Eegeo::v2>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_defaultStartPosition(defaultStartPosition)
            , m_targetPosition(targetPosition)
            , m_deltaPosition(Eegeo::v2::Zero())
            , m_currentStartPosition(Eegeo::v2::Zero())
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewPositionAnimator with NULL curve");
            }
            
            ViewPositionAnimator::~ViewPositionAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewPositionAnimator::OnPlay(bool playFromCurrent)
            {
                if(playFromCurrent)
                {
                    if(m_isPlayingForward)
                    {
                        m_currentStartPosition = Eegeo::dv2(m_view.frame.origin.x, m_view.frame.origin.y).ToSingle();
                        m_deltaPosition = m_targetPosition - m_currentStartPosition;
                    }
                    else
                    {
                        m_currentStartPosition = m_defaultStartPosition;
                        m_deltaPosition = Eegeo::dv2(m_view.frame.origin.x, m_view.frame.origin.y).ToSingle() - m_defaultStartPosition;
                    }
                }
                else
                {
                    m_currentStartPosition = m_defaultStartPosition;
                    m_deltaPosition = m_targetPosition - m_defaultStartPosition;
                }
            }
            
            void ViewPositionAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentPosition = (*m_curve)((float)timerSeconds, m_currentStartPosition, m_deltaPosition, (float)m_animationPeriodSeconds);
                
                CGRect frame = m_view.frame;
                frame.origin.x = std::ceil(currentPosition.x);
                frame.origin.y = std::ceil(currentPosition.y);
                m_view.frame = frame;
            }
        }
    }
}
