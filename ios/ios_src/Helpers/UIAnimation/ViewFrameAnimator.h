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
            class ViewFrameAnimator : public ViewAnimatorBase
            {
            private:
                Eegeo::v2 m_defaultStartPosition;
                Eegeo::v2 m_targetPosition;
                Eegeo::v2 m_deltaPosition;
                Eegeo::v2 m_currentStartPosition;
                Eegeo::v2 m_defaultStartSize;
                Eegeo::v2 m_targetSize;
                Eegeo::v2 m_deltaSize;
                Eegeo::v2 m_currentStartSize;
                Easing::IEasingCurve<Eegeo::v2>* m_pCurve;
                
            protected:
                void OnPlay();
                
                void OnPlayFromCurrent();
                
                void OnUpdate(double timerSeconds);
                
            public:
                ViewFrameAnimator(UIView* view,
                                  double animationPeriodSeconds,
                                  double startDelaySeconds,
                                  const Eegeo::v2& defaultStartPosition,
                                  const Eegeo::v2& targetPosition,
                                  const Eegeo::v2& defaultStartSize,
                                  const Eegeo::v2& targetSize,
                                  Easing::IEasingCurve<Eegeo::v2>* pCurve);
                
                ~ViewFrameAnimator();
            };
        }
    }
}
