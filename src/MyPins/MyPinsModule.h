// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinsModule.h"
#include "MyPins.h"
#include "Pins.h"
#include "WorldPins.h"
#include "PersistentSettings.h"
#include "Modules.h"
#include "Menu.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsModule : public IMyPinsModule
        {
        public:
            MyPinsModule(WorldPins::IWorldPinsService& worldPinsService,
                         Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                         PersistentSettings::IPersistentSettingsModel& persistentSettings,
                         ExampleApp::Menu::IMenuViewModel& menuViewModel,
                         ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinsModule();
            
            IMyPinsService& GetMyPinsService() const;
            Menu::IMenuModel& GetMyPinsMenuModel() const { return *m_pMenuModel; }
            
        private:
            MyPinsRepository* m_pMyPinsRepository;
            MyPinsFileIO* m_pMyPinsFileIO;
            MyPinsService* m_pMyPinsService;
            MyPinsRepositoryObserver* m_pMyPinsRepositoryObserver;
            
            Menu::IMenuModel* m_pMenuModel;
            Menu::IMenuOptionsModel* m_pMenuOptionsModel;
        };
    }
}