// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "CameraTransitions.h"
#include "Location.h"
#include "ICallback.h"
#include "NavRoutingRouteModel.h"
#include "Compass.h"
#include "AppCamera.h"
#include "MapCamera.h"

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
                                           Eegeo::Camera::MapCamera::MapCameraDistanceFromBoundsCalculator& cameraDistanceFromBoundsCalculator,
                                           Eegeo::Location::NavigationService& navigationService,
                                           Compass::SdkModel::ICompassModel& compassModel);
                
                ~NavRoutingCameraController();
                
            private:
                
                void OnRouteSet(const NavRoutingRouteModel& routeModel);
                void OnSelectedDirectionSet(const int& selectedDirection);
                void OnNavModeSet(const NavRoutingMode& navMode);
                void OnGpsModeChanged();
                
                void UpdateCamera();
                void SetCameraToSelectedDirection();
                void SetCameraToRouteOverview();
                void GetFirstSectionCentroidAndBounds(
                        const Eegeo::Routes::Webservice::RouteData& route,
                        Eegeo::Space::LatLong& out_centroid,
                        Eegeo::Space::LatLong& out_boundsNE,
                        Eegeo::Space::LatLong& out_boundsSW);
                
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const int> m_selectedDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingCameraController, const NavRoutingMode> m_navModeSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingCameraController> m_gpsModeChangedCallback;
                
                INavRoutingModel& m_navRoutingModel;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::Camera::MapCamera::MapCameraDistanceFromBoundsCalculator& m_cameraDistanceFromBoundsCalculator;
                Eegeo::Location::NavigationService& m_navigationService;
                Compass::SdkModel::ICompassModel& m_compassModel;

            };
        }
    }
}
