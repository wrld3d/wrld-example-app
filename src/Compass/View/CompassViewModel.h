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

                Eegeo::Helpers::TIdentity GetIdentity() const override;

                void AddToScreen() override;

                void RemoveFromScreen() override;

                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback) override;

                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback1<ScreenControl::View::IScreenControlViewModel&>& callback) override;

                bool IsOffScreen() const override;

                bool IsOnScreen() const override;

                ScreenControl::View::IMultiStateScreenControlViewModel& GetScreenControlViewModel();

                void SetState( ScreenControl::View::TScreenControlViewState state) override;

                ScreenControl::View::TScreenControlViewState GetState() override;

            private:
                CompassScreenControl m_screenControl;
            };
        }
    }
}
