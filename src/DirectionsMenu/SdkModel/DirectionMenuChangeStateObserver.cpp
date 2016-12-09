// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuChangeStateObserver.h"
#include "WorldPinItemModel.h"
#include "WorldPinOnMapController.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            
            DirectionMenuChangeStateObserver::DirectionMenuChangeStateObserver(ExampleApp::Menu::View::MenuController& directionsMenuController, WorldPins::View::WorldPinOnMapController& worldPinOnMapController, WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController, WorldPins::SdkModel::IWorldPinsInFocusController& worldPinsInFocusController)
            : m_directionsMenuController(directionsMenuController)
            , m_worldPinOnMapController(worldPinOnMapController)
            , m_onDirectionMenuStateChangeCallBackdCallback(this,& DirectionMenuChangeStateObserver::OnDirectionMenustateChange)
            , m_worldPinsScaleController(worldPinsScaleController)
            , m_worldPinsInFocusController(worldPinsInFocusController)
            {
                m_directionsMenuController.AddDirectionMenuStateUpdateCallBack(m_onDirectionMenuStateChangeCallBackdCallback);
            }
            
            DirectionMenuChangeStateObserver::~DirectionMenuChangeStateObserver()
            {
                m_directionsMenuController.RemoveDirectionMenuStateUpdateCallBack(m_onDirectionMenuStateChangeCallBackdCallback);
                //m_worldPinOnMapController.OnScreenStateUpdated((1.0),true);

            }
            
            void DirectionMenuChangeStateObserver::OnDirectionMenustateChange(const float& state, bool &openState)
            {
                m_worldPinsInFocusController.SetDiretionMenuState(openState);
                m_worldPinOnMapController.OnScreenStateUpdated((1.0-state),openState);
                m_worldPinsScaleController.SetDirectionMenuOpen(openState);
                m_worldPinsScaleController.SetModality(state);
            }

        }
    }
}