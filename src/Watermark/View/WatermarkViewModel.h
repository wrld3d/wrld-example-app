// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "WatermarkScreenControl.h"
#include "IIdentity.h"
#include "IWatermarkViewModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkViewModel : public IWatermarkViewModel, private Eegeo::NonCopyable
            {
            public:

                WatermarkViewModel(Eegeo::Helpers::TIdentity identity,
                                       bool isInitiallyOnScreen);

                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback);

                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback);

                bool IsOffScreen() const;

                bool IsOnScreen() const;

                float OnScreenState() const;
                
                bool IsAddedToScreen() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();

            private:
                WatermarkScreenControl m_screenControl;
            };
        }
    }
}
