// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            class ViewAnimatorBase
            {
            private:
                bool m_isActive;
                
            protected:
                UIView* m_pView;
                bool m_isPlayingForward;
                double m_animationPeriodSeconds;
                double m_startDelaySeconds;
                
                virtual void OnPlay() = 0;
                
                virtual void OnPlayFromCurrent() = 0;
                
                virtual void OnUpdate(double timerSeconds) = 0;
                
            public:
                ViewAnimatorBase(UIView* pView,
                                 double animationPeriodSeconds,
                                 double startDelaySeconds);
                
                virtual ~ViewAnimatorBase();
                
                void Play(bool isPlayingForward);
                
                void PlayFromCurrent(bool isPlayingForward);
                
                void Update(double timerSeconds);
                
                void UpdateToIntermediate(double timerSeconds);
                
                bool IsActive() const;
                
                double DurationSeconds() const;
                
                UIView* GetView() const;
            };
        }
    }
}