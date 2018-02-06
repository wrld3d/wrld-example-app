// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsLocationServiceController.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "ICompassModel.h"
#include "InteriorsCameraController.h"
#include "InteriorsExplorerModel.h"
#include "AppModeModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            InteriorsLocationServiceController::InteriorsLocationServiceController(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                                   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                   InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                                   Compass::SdkModel::ICompassModel& compassModel,
                                                                                   AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_currentLocationService(currentLocationService)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_compassModel(compassModel)
            , m_appModeModel(appModeModel)
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
                    Eegeo::Resources::Interiors::InteriorId newInteriorId = m_currentLocationService.GetInteriorId();
                    Eegeo::Resources::Interiors::InteriorId currInteriorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    if(newInteriorId != currInteriorId)
                    {
                        if (currInteriorId.IsValid())
                        {
                            m_interiorsExplorerModel.Exit();
                        }
                        else if(m_appModeModel.GetAppMode() == ExampleApp::AppModes::SdkModel::WorldMode)
                        {
                            m_interiorSelectionModel.SelectInteriorId(newInteriorId);
                        }
                    }
                    
                    int currentVisibleFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    
                    int floorIndex = 0;

                    if(m_currentLocationService.GetFloorIndex(floorIndex) &&
                       currentVisibleFloorIndex != floorIndex &&
                       m_interiorInteractionModel.HasInteriorModel())
                    {
                        m_interiorInteractionModel.SetSelectedFloorIndex(floorIndex);
                    }
                }
            }
        }
    }
}
