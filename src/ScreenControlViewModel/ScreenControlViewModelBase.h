// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace ScreenControlViewModel
    {
        class ScreenControlViewModelBase : public IScreenControlViewModel
        {
        private:
            float m_onScreenState;
            
            Eegeo::Helpers::CallbackCollection2<IScreenControlViewModel&, float> m_onScreenStateChangedCallbacks;
        
        protected:
            ScreenControlViewModelBase(bool isInitiallyOnScreen);
            
        public:
            
            ~ScreenControlViewModelBase();
            
            void AddToScreen();
           
            void RemoveFromScreen();
            
            void UpdateOnScreenState(float onScreenState);
            
            void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback);
            
            void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback);
            
            bool IsFullyOffScreen() const;
            
            bool IsFullyOnScreen() const;
            
            float OnScreenState() const;
        };
    }
}
