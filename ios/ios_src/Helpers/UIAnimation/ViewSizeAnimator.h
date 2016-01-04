// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ViewAnimatorBase.h"

#import <UIKit/UIKit.h>

#include "IEasingCurve.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            class ViewSizeAnimator : public ViewAnimatorBase
            {
            private:
                Eegeo::v2 m_startSize;
                Eegeo::v2 m_targetSize;
                Eegeo::v2 m_deltaSize;
                Easing::IEasingCurve<Eegeo::v2>* m_curve;
                
            protected:
                void OnUpdate(double timerSeconds);
                
            public:
                ViewSizeAnimator(UIView* view,
                                 double animationPeriodSeconds,
                                 double startDelaySeconds,
                                 const Eegeo::v2& startSize,
                                 const Eegeo::v2& targetSize,
                                 Easing::IEasingCurve<Eegeo::v2>* curve);
                
                ~ViewSizeAnimator();
            };
        }
    }
}
