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
                                           Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                
                ~InteriorsNavigationService();
                
                void SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode);
                
                Eegeo::Location::NavigationService::GpsMode GetGpsMode() const;
                
                void Update(float dt);
                
                bool IsPositionInInterior();
                
            private:
                
                void HandleInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& prevId);
                
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_cameraTouchController;
                Eegeo::Location::NavigationService::GpsMode m_gpsMode;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
                Eegeo::Helpers::TCallback1<InteriorsNavigationService, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedHandler;
                
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