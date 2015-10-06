// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            class IScreenControlViewModel : public Eegeo::Helpers::IIdentity
            {
            public:
                virtual ~IScreenControlViewModel() { }

                virtual void AddToScreen() = 0;

                virtual void RemoveFromScreen() = 0;

                virtual void UpdateOnScreenState(float onScreenState) = 0;

                virtual void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback) = 0;

                virtual void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback) = 0;

                virtual bool IsFullyOffScreen() const = 0;

                virtual bool IsFullyOnScreen() const = 0;

                virtual float OnScreenState() const = 0;
                
                virtual bool IsAddedToScreen() const = 0;
            };
        }
    }
}
