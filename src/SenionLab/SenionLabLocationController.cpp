// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "IPSConfigurationParser.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationController::SenionLabLocationController(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
        : m_appModeModel(appModeModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_interiorMetaDataRepository(interiorMetaDataRepository)
        , m_messageBus(messageBus)
        , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
        {
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        SenionLabLocationController::~SenionLabLocationController()
        {
            m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        void SenionLabLocationController::OnAppModeChanged()
        {

            
            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;

                if(interiorId.IsValid())
                {
                    InteriorsPosition::TryAndGetInteriorTrackingInfo(interiorTrackingInfoList, interiorId, m_interiorMetaDataRepository);
                }
                else
                {
                    return;
                }
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = interiorTrackingInfoList;
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = trackingInfoMap.find(interiorId.Value());
            	if(it != trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;
                    if(trackingInfo.GetType() == "Senion")
                    {
                        std::string apiKey = trackingInfo.GetConfig().GetApiKey();
                        std::string apiSecret = trackingInfo.GetConfig().GetApiSecret();
                        std::map<int, std::string> floorMap = trackingInfo.GetFloorIndexMap();
                        ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage message(apiKey,
                                                                                                             apiSecret,
                                                                                                             floorMap,
                                                                                                             0);
                        m_messageBus.Publish(message);
                    }
                }
            }
            else
            {
                m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage());
            }
        }
    }
}
