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
        SenionLabLocationController::SenionLabLocationController(SenionLabLocationManager& locationManager,
                                                                 ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                        						 ExampleAppMessaging::TMessageBus& messageBus)
        : m_locationManager(locationManager)
        , m_appModeModel(appModeModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_applicationConfiguration(applicationConfiguration)
        , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
        , m_messageBus(messageBus)
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
         
            [&m_locationManager StopUpdatingLocation];
         
            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = m_applicationConfiguration.InteriorTrackingInfo();
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = trackingInfoMap.find(interiorId.Value());
         
                if(it != trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;
         
                    if(trackingInfo.GetType() == "Senion")
                    {
                        NSString* apiKey = [NSString stringWithCString:trackingInfo.GetConfig().GetApiKey().c_str() encoding:[NSString defaultCStringEncoding]];
                        NSString* apiSecret = [NSString stringWithCString:trackingInfo.GetConfig().GetApiSecret().c_str() encoding:[NSString defaultCStringEncoding]];
                        std::map<int, std::string> floorMap = trackingInfo.GetFloorIndexMap();
         
                        [&m_locationManager StartUpdatingLocation: apiKey
                                                        apiSecret: apiSecret
                                                         floorMap: floorMap];
                        m_messageBus.Publish(ExampleApp::AboutPage::AboutPageSenionSettingsTypeMessage(std::string([apiKey UTF8String]), std::string([apiSecret UTF8String]), floorMap, it->second.GetInteriorId().Value()));
                    }
                }
            }
        }
    }
}