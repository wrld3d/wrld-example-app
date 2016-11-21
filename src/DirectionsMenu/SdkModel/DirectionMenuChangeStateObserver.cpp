// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuChangeStateObserver.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            
            DirectionMenuChangeStateObserver::DirectionMenuChangeStateObserver(ExampleApp::Menu::View::MenuController& directionsMenuController, WorldPins::View::WorldPinOnMapController& worldPinOnMapController)
            : m_directionsMenuController(directionsMenuController)
            , m_worldPinOnMapController(worldPinOnMapController)
            , m_onDirectionMenuStateChangeCallBackdCallback(this,& DirectionMenuChangeStateObserver::OnDirectionMenustateChange)
            {
                m_directionsMenuController.AddDirectionMenuStateUpdateCallBack(m_onDirectionMenuStateChangeCallBackdCallback);
            }
            
            DirectionMenuChangeStateObserver::~DirectionMenuChangeStateObserver()
            {
                m_directionsMenuController.RemoveDirectionMenuStateUpdateCallBack(m_onDirectionMenuStateChangeCallBackdCallback);
            }
            
            void DirectionMenuChangeStateObserver::OnDirectionMenustateChange(const float& state)
            {
                m_worldPinOnMapController.OnScreenStateUpdated(1.0-state);
            }

        }
    }
}