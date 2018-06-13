// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IIdentity.h"
#include "IScreenControlView.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            class IScreenControlViewModel : public virtual Eegeo::Helpers::IIdentity
            {
            public:
                virtual ~IScreenControlViewModel() { }

                virtual void AddToScreen() = 0;

                virtual void RemoveFromScreen() = 0;

                virtual void InsertOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback) = 0;

                virtual void RemoveOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback) = 0;

                virtual bool IsOffScreen() const = 0;

                virtual bool IsOnScreen() const = 0;
            };

            class IMultiStateScreenControlViewModel : public virtual IScreenControlViewModel
            {
            public:
                virtual TScreenControlViewState GetState() = 0;

                virtual void SetState(TScreenControlViewState state) = 0;
            };
        }
    }
}
