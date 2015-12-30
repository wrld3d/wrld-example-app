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
                                                       double animationPeriodSeconds,
                                                       double startDelaySeconds,
                                                       const Eegeo::v2& startPosition,
                                                       const Eegeo::v2& targetPosition,
                                                       Easing::IEasingCurve<Eegeo::v2>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_startPosition(startPosition)
            , m_targetPosition(targetPosition)
            , m_deltaPosition(m_targetPosition - m_startPosition)
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewPositionAnimator with NULL curve");
            }
            
            ViewPositionAnimator::~ViewPositionAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewPositionAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentPositon = (*m_curve)((float)timerSeconds, m_startPosition, m_deltaPosition, (float)m_animationPeriodSeconds);
                
                CGRect frame = m_view.frame;
                frame.origin.x = currentPositon.x;
                frame.origin.y = currentPositon.y;
                m_view.frame = frame;
            }
        }
    }
}
