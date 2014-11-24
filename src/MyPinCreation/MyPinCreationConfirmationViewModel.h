// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "MyPinCreationScreenControl.h"
#include "IIdentity.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "MyPinCreation.h"
#include "CallbackCollection.h"
#include "MyPinCreationConfirmationOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationConfirmationViewModel : public IMyPinCreationConfirmationViewModel, private Eegeo::NonCopyable
        {
        public:
            
            MyPinCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                                               bool isInitiallyOnScreen,
                                               Reaction::IReactionControllerModel& reactionControllerModel);

            
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

            OpenableControlViewModel::IOpenableControlViewModel& GetOpenableControlViewModel();

            bool TryOpen();
            
            void Close();
            
        private:
            MyPinCreationScreenControl m_screenControl;
            MyPinCreationConfirmationOpenableControl m_openable;
        };
    }
}
