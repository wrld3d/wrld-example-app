// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ViewAnimatorBase.h"

#import <UIKit/UIKit.h>

#include "IEasingCurve.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            class ViewAlphaAnimator : public ViewAnimatorBase
            {
            private:
                float m_startAlpha;
                float m_targetAlpha;
                float m_deltaAlpha;
                Easing::IEasingCurve<float>* m_curve;
                
            protected:
                void OnUpdate(double timerSeconds);
                
            public:
                ViewAlphaAnimator(UIView* view,
                                  double animationPeriodSeconds,
                                  double startDelaySeconds,
                                  float startAlpha,
                                  float targetAlpha,
                                  Easing::IEasingCurve<float>* curve);
                
                ~ViewAlphaAnimator();
            };
        }
    }
}
