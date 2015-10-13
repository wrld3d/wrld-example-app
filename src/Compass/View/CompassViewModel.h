// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "ICompassModel.h"
#include "CompassScreenControl.h"
#include "IIdentity.h"
#include "ICompassViewModel.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewModel : public ICompassViewModel, private Eegeo::NonCopyable
            {
            public:

                CompassViewModel(Eegeo::Helpers::TIdentity identity,
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

            private:
                CompassScreenControl m_screenControl;
            };
        }
    }
}
