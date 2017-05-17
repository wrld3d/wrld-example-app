// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewAnimationController.h"

#include "Types.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            ViewAnimationController::ViewAnimationController(UIView* pMainView,
                                                             OnAnimationComplete forwardCompleteCallback,
                                                             OnAnimationComplete reverseCompleteCallback)
            : m_pMainView(pMainView)
            , m_forwardCompleteCallback(forwardCompleteCallback)
            , m_reverseCompleteCallback(reverseCompleteCallback)
            , m_timerSeconds(0.0)
            , m_totalDurationSeconds(0.0)
            , m_isPlayingForward(true)
            {
                
            }
            
            ViewAnimationController::~ViewAnimationController()
            {
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    Eegeo_DELETE (*it);
                }
            }
            
            void ViewAnimationController::StartAnimators()
            {
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    (*it)->Play(m_isPlayingForward);
                }
            }
            
            void ViewAnimationController::StartAnimatorsFromCurrent()
            {
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    (*it)->PlayFromCurrent(m_isPlayingForward);
                }
            }
            
            void ViewAnimationController::AddAnimator(ViewAnimatorBase* animator)
            {
                Eegeo_ASSERT(animator != NULL, "NULL animator passed to animation controller");
                
                m_totalDurationSeconds = fmax(m_totalDurationSeconds, animator->DurationSeconds());
                
                m_animators.push_back(animator);
            }
            
            void ViewAnimationController::DeleteAnimatorsForView(UIView* view)
            {
                for(std::vector<ViewAnimatorBase*>::iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    if((*it)->GetView() == view)
                    {
                        Eegeo_DELETE (*it);
                        it = m_animators.erase(it);
                        
                        if(it == m_animators.end())
                        {
                            break;
                        }
                    }
                }
            }
            
            void ViewAnimationController::Play()
            {
                m_isPlayingForward = true;
                m_timerSeconds = 0.0;
                
                StartAnimators();
            }
            
            void ViewAnimationController::PlayReverse()
            {
                m_isPlayingForward = false;
                m_timerSeconds = m_totalDurationSeconds;
                
                StartAnimators();
            }
            
            void ViewAnimationController::PlayWithNormalizedOffset(float offset)
            {
                Eegeo_ASSERT(offset >= 0.0f && offset <= 1.0f, "Normalized offset should be between one and zero (inclusive)");
                
                m_isPlayingForward = true;
                m_timerSeconds = offset * m_totalDurationSeconds;
                
                StartAnimators();
            }
            
            void ViewAnimationController::PlayReverseWithNormalizedOffset(float offset)
            {
                Eegeo_ASSERT(offset >= 0.0f && offset <= 1.0f, "Normalized offset should be between one and zero (inclusive)");
                
                m_isPlayingForward = false;
                m_timerSeconds = (1.0f - offset) * m_totalDurationSeconds;
                
                StartAnimators();
            }
            
            void ViewAnimationController::PlayFromCurrent()
            {
                m_isPlayingForward = true;
                m_timerSeconds = 0.0;
                
                StartAnimatorsFromCurrent();
            }
            
            void ViewAnimationController::PlayReverseFromCurrent()
            {
                m_isPlayingForward = false;
                m_timerSeconds = m_totalDurationSeconds;
                
                StartAnimatorsFromCurrent();
            }
            
            void ViewAnimationController::SetToNormalizedOffset(float offset)
            {
                m_timerSeconds = offset * m_totalDurationSeconds;
                
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    (*it)->UpdateToIntermediate(m_timerSeconds);
                }
            }
            
            void ViewAnimationController::SetToEnd()
            {
                m_timerSeconds = m_isPlayingForward ? m_totalDurationSeconds : 0.0;
            }
            
            void ViewAnimationController::Update(double deltaSeconds)
            {
                Eegeo_ASSERT(IsActive(), "Trying to update an inactive ViewAnimationController, please check IsActive() before updating");
                
                if(m_isPlayingForward)
                {
                    m_timerSeconds = fmin(m_timerSeconds + deltaSeconds, m_totalDurationSeconds);
                }
                else
                {
                    m_timerSeconds = fmax(m_timerSeconds - deltaSeconds, 0.0);
                }
                
                bool activeAnimations = false;
                
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    if((*it)->IsActive())
                    {
                        (*it)->Update(m_timerSeconds);
                        
                        if((*it)->IsActive())
                        {
                            activeAnimations = true;
                        }
                    }
                }
                
                if(!activeAnimations)
                {
                    if(m_isPlayingForward && m_forwardCompleteCallback != NULL)
                    {
                        m_forwardCompleteCallback(m_pMainView);
                    }
                    else if(!m_isPlayingForward && m_reverseCompleteCallback != NULL)
                    {
                        m_reverseCompleteCallback(m_pMainView);
                    }
                }
            }
            
            bool ViewAnimationController::IsActive() const
            {
                for(std::vector<ViewAnimatorBase*>::const_iterator it = m_animators.begin(); it != m_animators.end(); ++it)
                {
                    if((*it)->IsActive())
                    {
                        return true;
                    }
                }
                
                return false;
            }
            
            float ViewAnimationController::GetNormalizedLinearProgress() const
            {
                return (float)(m_timerSeconds / m_totalDurationSeconds);
            }
            
            bool ViewAnimationController::IsPlayingForward() const
            {
                return m_isPlayingForward;
            }
        }
    }
}
