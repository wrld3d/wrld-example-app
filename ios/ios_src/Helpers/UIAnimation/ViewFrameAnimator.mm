// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewFrameAnimator.h"

#include <Types.h>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewFrameAnimator::ViewFrameAnimator(UIView* view,
                                                 double animationPeriodSeconds,
                                                 double startDelaySeconds,
                                                 const Eegeo::v2& startPosition,
                                                 const Eegeo::v2& targetPosition,
                                                 const Eegeo::v2& startSize,
                                                 const Eegeo::v2& targetSize,
                                                 Easing::IEasingCurve<Eegeo::v2>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_startPosition(startPosition)
            , m_targetPosition(targetPosition)
            , m_deltaPosition(m_targetPosition - m_startPosition)
            , m_startSize(startSize)
            , m_targetSize(targetSize)
            , m_deltaSize(m_targetSize - m_startSize)
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewFrameAnimator with NULL curve");
            }
            
            ViewFrameAnimator::~ViewFrameAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewFrameAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentPositon = (*m_curve)((float)timerSeconds, m_startPosition, m_deltaPosition, (float)m_animationPeriodSeconds);
                const Eegeo::v2& currentSize = (*m_curve)((float)timerSeconds, m_startSize, m_deltaSize, (float)m_animationPeriodSeconds);
                
                m_view.frame = CGRectMake(currentPositon.x, currentPositon.y, currentSize.x, currentSize.y);
            }
        }
    }
}
