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
                bool m_isPlayingForward;
                
            protected:
                UIView* m_view;
                double m_animationPeriodSeconds;
                double m_startDelaySeconds;
                
                virtual void OnUpdate(double timerSeconds) = 0;
                
            public:
                ViewAnimatorBase(UIView* view,
                                 double animationPeriodSeconds,
                                 double startDelaySeconds);
                
                virtual ~ViewAnimatorBase();
                
                void Play(bool isPlayingForward);
                
                void Update(double timerSeconds);
                
                bool IsActive() const;
                
                double DurationSeconds() const;
                
                UIView* GetView() const;
            };
        }
    }
}