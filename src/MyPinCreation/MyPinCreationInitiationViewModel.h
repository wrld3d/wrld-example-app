// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "MyPinCreationScreenControl.h"
#include "IIdentity.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "MyPinCreation.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationInitiationViewModel : public IMyPinCreationInitiationViewModel, private Eegeo::NonCopyable
        {
        public:
            
            MyPinCreationInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                                             bool isInitiallyOnScreen);
            
            Eegeo::Helpers::TIdentity GetIdentity() const;
            
            void AddToScreen();
            
            void RemoveFromScreen();
            
            void UpdateOnScreenState(float onScreenState);
            
            void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback);
            
            void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback);
            
            bool IsFullyOffScreen() const;
            
            bool IsFullyOnScreen() const;
            
            float OnScreenState() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel();
            
            bool ShouldOffsetViewButton() const;
            
            void SetShouldOffsetViewButton(bool shouldOffset);
            
        private:
            MyPinCreationScreenControl m_screenControl;
            bool m_shouldOffsetViewButton;
        };
    }
}
