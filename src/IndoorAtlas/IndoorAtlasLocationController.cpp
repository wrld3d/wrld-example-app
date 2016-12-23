// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "InteriorsPositionFloorChangedMessage.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        IndoorAtlasLocationController::IndoorAtlasLocationController(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                     const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                                     ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
        : m_appModeModel(appModeModel)
        , m_interiorInteractionModel(interiorInteractionModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_appModeChangedCallback(this, &IndoorAtlasLocationController::OnAppModeChanged)
        , m_floorSelectedCallback(this, &IndoorAtlasLocationController::OnFloorSelected)
        , m_trackingInfoMap(applicationConfiguration.InteriorTrackingInfo())
        , m_messageBus(messageBus)
        {
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_floorSelectedCallback);
        }
        
        IndoorAtlasLocationController::~IndoorAtlasLocationController()
        {
            m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            m_interiorInteractionModel.UnregisterModelChangedCallback(m_floorSelectedCallback);
        }
        
        void IndoorAtlasLocationController::OnAppModeChanged()
        {
        	Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
            int currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();

            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = m_trackingInfoMap.find(interiorId.Value());
                if(it != m_trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = (*it).second;
                    if(trackingInfo.GetType() == "IndoorAtlas")
                    {
                        std::string apiKey = trackingInfo.GetConfig().GetApiKey();
                        std::string apiSecret = trackingInfo.GetConfig().GetApiSecret();
                        std::map<int, std::string> floorMap = trackingInfo.GetFloorIndexMap();
                        ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage message(apiKey,
                                                                                                             apiSecret,
                                                                                                             floorMap,
                                                                                                             currentFloorIndex);
                        m_messageBus.Publish(message);
                    }
                }
            }
            else
            {
                m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage());
            }
        }
        
        void IndoorAtlasLocationController::OnFloorSelected()
        {
            int currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
            m_messageBus.Publish(ExampleApp::InteriorsPosition::InteriorsPositionFloorChangedMessage(currentFloorIndex));
        }
    }
}
