// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewFrameAnimator.h"

#include <cmath>
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
                                                 const Eegeo::v2& defaultStartPosition,
                                                 const Eegeo::v2& targetPosition,
                                                 const Eegeo::v2& defaultStartSize,
                                                 const Eegeo::v2& targetSize,
                                                 Easing::IEasingCurve<Eegeo::v2>* pCurve)
            : ViewAnimatorBase(view, animationPeriodSeconds, startDelaySeconds)
            , m_defaultStartPosition(defaultStartPosition)
            , m_targetPosition(targetPosition)
            , m_deltaPosition(Eegeo::v2::Zero())
            , m_currentStartPosition(Eegeo::v2::Zero())
            , m_defaultStartSize(defaultStartSize)
            , m_targetSize(targetSize)
            , m_deltaSize(Eegeo::v2::Zero())
            , m_currentStartSize(Eegeo::v2::Zero())
            , m_pCurve(pCurve)
            {
                Eegeo_ASSERT(m_pCurve != NULL, "Can't initialise ViewFrameAnimator with NULL curve");
            }
            
            ViewFrameAnimator::~ViewFrameAnimator()
            {
                Eegeo_DELETE m_pCurve;
            }
            
            void ViewFrameAnimator::OnPlay()
            {
                m_currentStartPosition = m_defaultStartPosition;
                m_deltaPosition = m_targetPosition - m_defaultStartPosition;
                
                m_currentStartSize = m_defaultStartSize;
                m_deltaSize = m_targetSize - m_defaultStartSize;
            }
            
            void ViewFrameAnimator::OnPlayFromCurrent()
            {
                if(m_isPlayingForward)
                {
                    m_currentStartPosition = Eegeo::dv2(m_pView.frame.origin.x, m_pView.frame.origin.y).ToSingle();
                    m_deltaPosition = m_targetPosition - m_currentStartPosition;
                    
                    m_currentStartSize = Eegeo::dv2(m_pView.frame.size.width, m_pView.frame.size.height).ToSingle();
                    m_deltaSize = m_targetSize - m_currentStartSize;
                }
                else
                {
                    m_currentStartPosition = m_defaultStartPosition;
                    m_deltaPosition = Eegeo::dv2(m_pView.frame.origin.x, m_pView.frame.origin.y).ToSingle() - m_defaultStartPosition;
                    
                    m_currentStartSize = m_defaultStartSize;
                    m_deltaSize = Eegeo::dv2(m_pView.frame.size.width, m_pView.frame.size.height).ToSingle() - m_defaultStartSize;
                }
            }
            
            void ViewFrameAnimator::OnUpdate(double timerSeconds)
            {
                const Eegeo::v2& currentPosition = (*m_pCurve)((float)timerSeconds, m_currentStartPosition, m_deltaPosition, (float)m_animationPeriodSeconds);
                const Eegeo::v2& currentSize = (*m_pCurve)((float)timerSeconds, m_currentStartSize, m_deltaSize, (float)m_animationPeriodSeconds);
                
                m_pView.frame = CGRectMake(std::ceil(currentPosition.x),
                                           std::ceil(currentPosition.y),
                                           std::ceil(currentSize.x),
                                           std::ceil(currentSize.y));
            }
        }
    }
}
