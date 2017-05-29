// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISenionLabLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationController
                {
                public:
                    SenionLabLocationController(ISenionLabLocationManager& locationManager,
                                                AppModes::SdkModel::IAppModeModel& appModeModel,
                                                const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                ExampleAppMessaging::TMessageBus& messageBus);
                    ~SenionLabLocationController();
                    
                private:
                    ISenionLabLocationManager& m_locationManager;
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Helpers::TCallback0<SenionLabLocationController> m_appModeChangedCallback;
                    Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    void OnAppModeChanged();
                };
            }
        }
    }
}
