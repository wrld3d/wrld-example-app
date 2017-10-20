// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsLocationServiceController.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
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
                                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                   Compass::SdkModel::ICompassModel& compassModel)
            : m_currentLocationService(currentLocationService)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModel(interiorSelectionModel)            , m_compassModel(compassModel)
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
                    if(m_currentLocationService.GetInteriorId() != m_interiorSelectionModel.GetSelectedInteriorId())
                    {
                        m_interiorSelectionModel.SelectInteriorId(m_currentLocationService.GetInteriorId());
                    }
                    
                    int currentVisibleFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    
                    int floorIndex = 0;
                    if(m_currentLocationService.GetFloorIndex(floorIndex) && currentVisibleFloorIndex != floorIndex)
                    {
                        m_interiorInteractionModel.SetSelectedFloorIndex(floorIndex);
                    }
                }
            }
        }
    }
}
