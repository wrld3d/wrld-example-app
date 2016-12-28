// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "AppModeModel.h"
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationController
        {
        public:
            SenionLabLocationController(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                        Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                        ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
            ~SenionLabLocationController();
            
        private:
            ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            Eegeo::Helpers::TCallback0<SenionLabLocationController> m_appModeChangedCallback;
            ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;

            void OnAppModeChanged();
            
            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
        };
    }
}
