// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "FlattenButtonScreenControl.h"
#include "IIdentity.h"
#include "IFlattenButtonViewModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewModel : public IFlattenButtonViewModel, private Eegeo::NonCopyable
            {
            public:

                FlattenButtonViewModel(Eegeo::Helpers::TIdentity identity,
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
                FlattenButtonScreenControl m_screenControl;
            };
        }
    }
}
