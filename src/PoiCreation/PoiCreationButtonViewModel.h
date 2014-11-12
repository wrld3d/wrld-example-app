// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "PoiCreationScreenControl.h"
#include "IIdentity.h"
#include "IPoiCreationButtonViewModel.h"
#include "PoiCreation.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationButtonViewModel : public IPoiCreationButtonViewModel, private Eegeo::NonCopyable
        {
        public:
            
            PoiCreationButtonViewModel(Eegeo::Helpers::TIdentity identity,
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
            PoiCreationScreenControl m_screenControl;
            bool m_shouldOffsetViewButton;
        };
    }
}
