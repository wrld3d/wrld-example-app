// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "PoiCreationConfirmationScreenControl.h"
#include "IIdentity.h"
#include "IPoiCreationConfirmationViewModel.h"
#include "PoiCreation.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationConfirmationViewModel : public IPoiCreationConfirmationViewModel, private Eegeo::NonCopyable
        {
        public:
            
            PoiCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
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
        private:
            PoiCreationConfirmationScreenControl m_screenControl;
        };
    }
}
