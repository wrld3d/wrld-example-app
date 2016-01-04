// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavigationService.h"
#include "IInteriorsNavigationService.h"
#include "GlobeCamera.h"
#include "Location.h"
#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            class InteriorsNavigationService : public IInteriorsNavigationService
            {
            public:
                
                InteriorsNavigationService(Eegeo::Location::ILocationService& locationService,
                                           InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsExplorerCameraController,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                           Eegeo::Resources::Interiors::InteriorController& interiorController);
                
                ~InteriorsNavigationService();
                
                void SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode);
                
                Eegeo::Location::NavigationService::GpsMode GetGpsMode() const;
                
                void Update(float dt);
                
                bool IsPositionInInterior();
                
            private:
                
                void HandleInteriorStateChanged();
                
                Eegeo::Location::ILocationService& m_locationService;
                InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsExplorerCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_cameraTouchController;
                Eegeo::Location::NavigationService::GpsMode m_gpsMode;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                
                Eegeo::Helpers::TCallback0<InteriorsNavigationService> m_interiorStateChangedHandler;
                
                double m_targetHeading;
                double m_currentHeading;
                
                double m_targetLongitude;
                double m_targetLatitude;
                
                double m_currentLongitude;
                double m_currentLatitude;
                
                void ResetTargetLatLong();
            };
            
        }
    }
}