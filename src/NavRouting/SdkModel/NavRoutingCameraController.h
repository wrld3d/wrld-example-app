// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "CameraTransitions.h"
#include "Location.h"
#include "ICallback.h"
#include "NavRoutingRouteModel.h"
#include "Compass.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingCameraController
            {
            public:
                
                NavRoutingCameraController(INavRoutingModel& navRoutingModel,
                                           CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                           Eegeo::Location::NavigationService& navigationService,
                                           Compass::SdkModel::ICompassModel& compassModel);
                
                ~NavRoutingCameraController();
                
            private:
                
                void OnRouteSet(const NavRoutingRouteModel& routeModel);
                void OnSelectedDirectionSet(const int& selectedDirection);
                void OnCurrentDirectionSet(const int& currentDirection);
                void OnNavModeSet(const NavRoutingMode& navMode);
                void OnGpsModeChanged();
                
                void UpdateCamera();
                void SetCameraToSelectedDirection();
                
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const int> m_selectedDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const int> m_currentDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const NavRoutingMode> m_navModeSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingCameraController> m_gpsModeChangedCallback;
                
                INavRoutingModel& m_navRoutingModel;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::Location::NavigationService& m_navigationService;
                Compass::SdkModel::ICompassModel& m_compassModel;
            };
        }
    }
}
