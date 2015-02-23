// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinsModule.h"
#include "MyPins.h"
#include "Pins.h"
#include "WorldPins.h"
#include "PersistentSettings.h"
#include "Modules.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsModule : public IMyPinsModule
            {
            public:
                MyPinsModule(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                             Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                             PersistentSettings::IPersistentSettingsModel& persistentSettings,
                             Menu::View::IMenuViewModel& menuViewModel,
                             ExampleAppMessaging::TMessageBus& messageBus,
                             CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);

                ~MyPinsModule();

                IMyPinsService& GetMyPinsService() const;
                
                IMyPinsRepository& GetMyPinsRepository() const;
                
                Menu::View::IMenuModel& GetMyPinsMenuModel() const
                {
                    return *m_pMenuModel;
                }

            private:
                MyPinsRepository* m_pMyPinsRepository;
                MyPinsFileIO* m_pMyPinsFileIO;
                MyPinsService* m_pMyPinsService;
                MyPinsRepositoryObserver* m_pMyPinsRepositoryObserver;
                MyPinSelectionHandlerFactory* m_pMyPinsSelectionHandlerFactory;
                View::MyPinAddedToMenuObserver* m_pMyPinAddedToMenuObserver;
                View::MyPinRemovedFromMenuObserver* m_pMyPinRemovedFromMenuObserver;
                MyPinSelectedMessageHandler* m_pMyPinSelectedMessageHandler;

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
            };
        }
    }
}
