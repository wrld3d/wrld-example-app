// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsLocationServiceController.h"
#include "InteriorInteractionModel.h"
#include "ICompassModel.h"
#include "InteriorsCameraController.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            InteriorsLocationServiceController::InteriorsLocationServiceController(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                                   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                   CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                   Compass::SdkModel::ICompassModel& compassModel,
                                                                                   float locationDistance)
                : m_currentLocationService(currentLocationService)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_cameraTransitionController(cameraTransitionController)
                , m_compassModel(compassModel)
                , m_hasLocationDistance(true)
                , m_locationDistance(locationDistance)
            {
            }

            InteriorsLocationServiceController::InteriorsLocationServiceController(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                                   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                   CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                   Compass::SdkModel::ICompassModel& compassModel)
                : m_currentLocationService(currentLocationService)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_cameraTransitionController(cameraTransitionController)
                , m_compassModel(compassModel)
                , m_hasLocationDistance(false)
                , m_locationDistance(0.0)
            {
            }

            InteriorsLocationServiceController::~InteriorsLocationServiceController()
            {
            }
            
            void InteriorsLocationServiceController::Update()
            {
                Compass::GpsMode::Values gpsMode = m_compassModel.GetGpsMode();
                if(gpsMode == Compass::GpsMode::GpsFollow || gpsMode == Compass::GpsMode::GpsCompassMode)
                {
                    int currentVisibleFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    
                    int floorIndex = 0;
                    if(m_currentLocationService.GetFloorIndex(floorIndex) && floorIndex >= 0 && currentVisibleFloorIndex != floorIndex)
                    {
                        Eegeo::Space::LatLong latLong(0, 0);
                        if(m_currentLocationService.GetLocation(latLong))
                        {
                            m_cameraTransitionController.StartTransitionTo(latLong.ToECEF(),
                                m_locationDistance,
                                0.0,                    
                                m_currentLocationService.GetInteriorId(),                                
                                floorIndex,                                
                                true,                                
                                false,                                
                                false,                                
                                m_hasLocationDistance);
                        }
                    }
                }
            }
        }
    }
}
