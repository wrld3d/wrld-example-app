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
                                               const Eegeo::v2& defaultStartSize,
                                               const Eegeo::v2& targetSize,
                                               Easing::IEasingCurve<Eegeo::v2>* pCurve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_defaultStartSize(defaultStartSize)
            , m_targetSize(targetSize)
            , m_deltaSize(Eegeo::v2::Zero())
            , m_currentStartSize(Eegeo::v2::Zero())
            , m_pCurve(pCurve)
            {
                Eegeo_ASSERT(m_pCurve != NULL, "Can't initialise ViewPositionAnimator with NULL curve");
            }
            
            ViewSizeAnimator::~ViewSizeAnimator()
            {
                Eegeo_DELETE m_pCurve;
            }
            
            void ViewSizeAnimator::OnPlay()
            {
                m_currentStartSize = m_defaultStartSize;
                m_deltaSize = m_targetSize - m_defaultStartSize;
            }
            
            void ViewSizeAnimator::OnPlayFromCurrent()
            {
                if(m_isPlayingForward)
                {
                    m_currentStartSize = Eegeo::dv2(m_pView.frame.size.width, m_pView.frame.size.height).ToSingle();
                    m_deltaSize = m_targetSize - m_currentStartSize;
                }
                else
                {
                    m_currentStartSize = m_defaultStartSize;
                    m_deltaSize = Eegeo::dv2(m_pView.frame.size.width, m_pView.frame.size.height).ToSingle() - m_defaultStartSize;
                }
            }
            
            void ViewSizeAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentSize = (*m_pCurve)((float)timerSeconds, m_currentStartSize, m_deltaSize, (float)m_animationPeriodSeconds);
                
                CGRect frame = m_pView.frame;
                frame.size.width = std::ceil(currentSize.x);
                frame.size.height = std::ceil(currentSize.y);
                m_pView.frame = frame;
            }
        }
    }
}
