// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "ICurve.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            class ViewPositionAnimator
            {
            public:
                typedef void(^OnAnimationComplete)(UIView*);
                
            private:
                UIView* m_view;
                Eegeo::v2 m_startPosition;
                Eegeo::v2 m_deltaPosition;
                Eegeo::v2 m_targetPosition;
                double m_animationPeriodSeconds;
                Curves::ICurve* m_curve;
                OnAnimationComplete m_endCallback;
                bool m_isActive;
                double m_timer;
                
            public:
                ViewPositionAnimator(UIView* view,
                                     const Eegeo::v2& targetPosition,
                                     double animationPeriodSeconds,
                                     Curves::ICurve* curve,
                                     OnAnimationComplete endCallback);
                
                ~ViewPositionAnimator();
                
                void Play();
                
                void PlayWithNormalizedOffset(float offset);
                
                void Update(double deltaSeconds);
                
                bool IsActive() const;
            };
        }
    }
}
