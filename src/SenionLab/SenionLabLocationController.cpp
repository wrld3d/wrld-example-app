// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationController::SenionLabLocationController(View::ISenionLabLocationManager& locationManager,
                                                                 ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration)
        : m_locationManager(locationManager)
        , m_appModeModel(appModeModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
        , m_trackingInfoMap(applicationConfiguration.InteriorTrackingInfo())
        {
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        SenionLabLocationController::~SenionLabLocationController()
        {
            m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        void SenionLabLocationController::OnAppModeChanged()
        {
        	Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
         
            m_locationManager.StopUpdatingLocation();
         
            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
            	const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = m_trackingInfoMap.find(interiorId.Value());
         
            	if(it != m_trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;
         
                    if(trackingInfo.GetType() == "Senion")
                    {
                        std::string apiKey = trackingInfo.GetConfig().GetApiKey();
                        std::string apiSecret = trackingInfo.GetConfig().GetApiSecret();
                        std::map<int, std::string> floorMap = trackingInfo.GetFloorIndexMap();
                        m_locationManager.StartUpdatingLocation(apiKey,
                                                                apiSecret,
                                                                floorMap);
                    }
                }
            }
        }
    }
}
