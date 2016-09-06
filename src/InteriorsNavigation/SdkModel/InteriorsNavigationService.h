// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "NavigationService.h"
#include "IInteriorsNavigationService.h"
#include "GlobeCamera.h"
#include "Location.h"
#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "ICallback.h"
#include "IInteriorCameraController.h"
#include <memory>

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            class InteriorsNavigationService : public IInteriorsNavigationService, private Eegeo::NonCopyable
            {
            public:
                
                InteriorsNavigationService(const std::shared_ptr<Eegeo::Location::ILocationService>& locationService,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController,
                                           const std::shared_ptr<InteriorsExplorer::SdkModel::IInteriorCameraController>& interiorCameraController,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel);
                
                ~InteriorsNavigationService();
                
                void SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode);
                
                Eegeo::Location::NavigationService::GpsMode GetGpsMode() const;
                
                void Update(float dt);
                
                bool IsPositionInInterior();
                
            private:
                
                void HandleInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& prevId);
                
                const std::shared_ptr<Eegeo::Location::ILocationService> m_locationService;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorsCameraController;
                const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController> m_cameraTouchController;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;

                Eegeo::Location::NavigationService::GpsMode m_gpsMode;
                
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