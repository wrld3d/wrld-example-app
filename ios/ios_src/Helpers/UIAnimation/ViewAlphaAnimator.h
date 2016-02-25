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
                float m_defaultStartAlpha;
                float m_targetAlpha;
                float m_deltaAlpha;
                float m_currentStartAlpha;
                Easing::IEasingCurve<float>* m_pCurve;
                
            protected:
                void OnPlay();
                
                void OnPlayFromCurrent();
                
                void OnUpdate(double timerSeconds);
                
            public:
                ViewAlphaAnimator(UIView* view,
                                  double animationPeriodSeconds,
                                  double startDelaySeconds,
                                  float defaultStartAlpha,
                                  float targetAlpha,
                                  Easing::IEasingCurve<float>* pCurve);
                
                ~ViewAlphaAnimator();
            };
        }
    }
}
