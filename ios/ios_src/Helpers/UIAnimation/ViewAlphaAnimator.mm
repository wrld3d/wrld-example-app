// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewAlphaAnimator.h"

#include "Types.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewAlphaAnimator::ViewAlphaAnimator(UIView* view,
                                                 double animationPeriodSeconds,
                                                 double startDelaySeconds,
                                                 float startAlpha,
                                                 float targetAlpha,
                                                 Easing::IEasingCurve<float>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_startAlpha(startAlpha)
            , m_targetAlpha(targetAlpha)
            , m_deltaAlpha(m_targetAlpha - m_startAlpha)
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewAlphaAnimator with NULL curve");
            }
            
            ViewAlphaAnimator::~ViewAlphaAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewAlphaAnimator::OnUpdate(double timerSeconds)
            {
                m_view.alpha = (*m_curve)((float)timerSeconds, m_startAlpha, m_deltaAlpha, (float)m_animationPeriodSeconds);
            }
        }
    }
}
