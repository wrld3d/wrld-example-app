// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            class ScreenControlViewModelBase : public virtual IScreenControlViewModel
            {
            private:
                bool m_addedToScreen;
                
                Eegeo::Helpers::CallbackCollection1<IScreenControlViewModel&> m_onScreenStateChangedCallbacks;

            protected:
                ScreenControlViewModelBase(bool isInitiallyOnScreen);

            public:

                ~ScreenControlViewModelBase();

                void AddToScreen();

                void RemoveFromScreen();

                void InsertOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                void RemoveOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                bool IsOffScreen() const;

                bool IsOnScreen() const;
            };
        }
    }
}
