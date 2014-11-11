// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
        class CompassViewModel : public ICompassViewModel, private Eegeo::NonCopyable
        {
        public:
            
            CompassViewModel(Eegeo::Helpers::TIdentity identity,
                             bool isInitiallyOnScreen);
            
            /*void UpdateHeadingAngleRadians(float headingRadians);
            
            void InsertUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback);
            
            void RemoveUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback);*/
            
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
            //ICompassModel& m_model;
            CompassScreenControl m_screenControl;
            //Eegeo::Helpers::CallbackCollection1<float> m_updateCallbacks;
        };
    }
}
