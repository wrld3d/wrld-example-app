// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "AppModeModel.h"
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        class IndoorAtlasLocationController
        {
        public:
            IndoorAtlasLocationController(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                          ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
            ~IndoorAtlasLocationController();
            
        private:
            ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> m_trackingInfoMap;
            ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            
            Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_floorSelectedCallback;
            Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_appModeChangedCallback;
            
            void OnAppModeChanged();
            void OnFloorSelected();
        };
    }
}
