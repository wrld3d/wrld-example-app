// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewSizeAnimator.h"

#include <cmath>
#include <Types.h>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewSizeAnimator::ViewSizeAnimator(UIView* view,
                                               double animationPeriodSeconds,
                                               double startDelaySeconds,
                                               const Eegeo::v2& startSize,
                                               const Eegeo::v2& targetSize,
                                               Easing::IEasingCurve<Eegeo::v2>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_startSize(startSize)
            , m_targetSize(targetSize)
            , m_deltaSize(m_targetSize - m_startSize)
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewPositionAnimator with NULL curve");
            }
            
            ViewSizeAnimator::~ViewSizeAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewSizeAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentSize = (*m_curve)((float)timerSeconds, m_startSize, m_deltaSize, (float)m_animationPeriodSeconds);
                
                CGRect frame = m_view.frame;
                frame.size.width = std::ceil(currentSize.x);
                frame.size.height = std::ceil(currentSize.y);
                m_view.frame = frame;
            }
        }
    }
}
