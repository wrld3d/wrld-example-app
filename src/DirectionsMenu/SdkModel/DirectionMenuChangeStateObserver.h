// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "WorldPinOnMapController.h"
#include "MenuController.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionMenuChangeStateObserver : private Eegeo::NonCopyable
            {
            
            public:
                
                DirectionMenuChangeStateObserver(ExampleApp::Menu::View::MenuController& directionsMenuController, WorldPins::View::WorldPinOnMapController& worldPinOnMapController);
                
                ~DirectionMenuChangeStateObserver();
            
            private:
                
                ExampleApp::Menu::View::MenuController& m_directionsMenuController;
                
                WorldPins::View::WorldPinOnMapController& m_worldPinOnMapController;
                
                Eegeo::Helpers::TCallback1<DirectionMenuChangeStateObserver,const float&>  m_onDirectionMenuStateChangeCallBackdCallback;
                
                
                void OnDirectionMenustateChange(const float& state);

            };
        }
    }
}