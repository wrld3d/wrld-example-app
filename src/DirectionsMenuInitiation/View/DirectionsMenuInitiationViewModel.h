// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "DirectionsMenuInitiationScreenControl.h"
#include "IIdentity.h"
#include "IDirectionsMenuInitiationViewModel.h"
#include "DirectionsMenuInitiation.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class DirectionsMenuInitiationViewModel : public IDirectionsMenuInitiationViewModel, private Eegeo::NonCopyable
            {
            public:

                DirectionsMenuInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                                                 bool isInitiallyOnScreen);

                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void UpdateOnScreenState(float onScreenState);

                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                bool IsFullyOffScreen() const;

                bool IsFullyOnScreen() const;

                float OnScreenState() const;
                
                bool IsAddedToScreen() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();

                bool ShouldOffsetViewButton() const;

                void SetShouldOffsetViewButton(bool shouldOffset);

            private:
                DirectionsMenuInitiationScreenControl m_screenControl;
                bool m_shouldOffsetViewButton;
            };
        }
    }
}
