// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#import "ISenionLabModule.h"
#include "IAvatarController.h"
#import "Types.h"
#import "SenionLabLocationManager.h"
#include "IndoorLocation.h"
#include <string>
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace SenionLab
    {

        class SenionLabModule: public ExampleApp::SenionLab::ISenionLabModule, private Eegeo::NonCopyable
            {
            
            private:
                SenionLabLocationManager* m_pLoctionManager;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Helpers::TCallback0<SenionLabModule> m_appModeChangedCallback;
                ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *m_deviceModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>m_buildingsInfoList;
                
                
                
                void OnAppModeChanged();
                ExampleApp::ApplicationConfig::ApplicationBuildingInfo* getBuildingInfo(Eegeo::Resources::Interiors::InteriorId interiorID);
                void InitlizeSenionLocationManagerWithInteriorID(ExampleApp::ApplicationConfig::ApplicationBuildingInfo *respectiveBuilding);

            public:
                SenionLabModule(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *deviceModel,
                                ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&buildingsInfo);
                
                ~SenionLabModule();                

            };
    }
}

