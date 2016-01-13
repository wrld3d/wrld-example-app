// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewAlphaAnimator.h"

#include <cmath>
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
                                                 float defaultStartAlpha,
                                                 float targetAlpha,
                                                 Easing::IEasingCurve<float>* curve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_defaultStartAlpha(defaultStartAlpha)
            , m_targetAlpha(targetAlpha)
            , m_deltaAlpha(0.0f)
            , m_currentStartAlpha(0.0f)
            , m_curve(curve)
            {
                Eegeo_ASSERT(m_curve != NULL, "Can't initialise ViewAlphaAnimator with NULL curve");
            }
            
            ViewAlphaAnimator::~ViewAlphaAnimator()
            {
                Eegeo_DELETE m_curve;
            }
            
            void ViewAlphaAnimator::OnPlay()
            {
                m_currentStartAlpha = m_defaultStartAlpha;
                m_deltaAlpha = m_targetAlpha - m_defaultStartAlpha;
            }
            
            void ViewAlphaAnimator::OnPlayFromCurrent()
            {
                if(m_isPlayingForward)
                {
                    m_currentStartAlpha = static_cast<float>(m_view.alpha);
                    m_deltaAlpha = m_targetAlpha - m_currentStartAlpha;
                }
                else
                {
                    m_currentStartAlpha = m_defaultStartAlpha;
                    m_deltaAlpha = static_cast<float>(m_view.alpha) - m_defaultStartAlpha;
                }
            }
            
            void ViewAlphaAnimator::OnUpdate(double timerSeconds)
            {
                m_view.alpha = std::ceil((*m_curve)((float)timerSeconds, m_currentStartAlpha, m_deltaAlpha, (float)m_animationPeriodSeconds));
            }
        }
    }
}
