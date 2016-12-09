// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "WorldPinOnMapController.h"
#include "MenuController.h"
#include "IWorldPinsRepository.h"
#include "IWorldPinsService.h"
#include "IWorldPinsScaleController.h"
#include "IWorldPinsInFocusController.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionMenuChangeStateObserver : private Eegeo::NonCopyable
            {
            
            public:
                
                DirectionMenuChangeStateObserver(ExampleApp::Menu::View::MenuController& directionsMenuController,
                                                 WorldPins::View::WorldPinOnMapController& worldPinOnMapController,
                                                 WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                 WorldPins::SdkModel::IWorldPinsInFocusController& worldPinsInFocusController);
                
                ~DirectionMenuChangeStateObserver();
            
            private:
                
                ExampleApp::Menu::View::MenuController& m_directionsMenuController;
                
                WorldPins::View::WorldPinOnMapController& m_worldPinOnMapController;
                
                WorldPins::SdkModel::IWorldPinsScaleController& m_worldPinsScaleController;
                
                WorldPins::SdkModel::IWorldPinsInFocusController& m_worldPinsInFocusController;
                
                Eegeo::Helpers::TCallback2<DirectionMenuChangeStateObserver,const float&,bool&>  m_onDirectionMenuStateChangeCallBackdCallback;
                
                void OnDirectionMenustateChange(const float& state, bool& openState);

            };
        }
    }
}