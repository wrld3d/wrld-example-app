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
#include "SdkModelDomainEventBus.h"
#include "CameraTransitions.h"
#include "TagSearch.h"
#include "Search.h"
#include "IMetricsService.h"
#include "Helpers.h"
#include <string>
#include "IMenuReactionModel.h"
#include "IMenuIgnoredReactionModel.h"

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
                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                             CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                             Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                             Metrics::IMetricsService& metricsService,
                             const std::string& myPinsWebServiceUrl,
                             const std::string& myPinsWebServiceAuthToken,
                             const std::string& myPinsPoiSetId,
                             const Menu::View::IMenuReactionModel& menuReaction,
                             Menu::View::IMenuIgnoredReactionModel& ignoredMenuReaction);

                ~MyPinsModule();

                IMyPinsService& GetMyPinsService() const;
                
                Menu::View::IMenuModel& GetMyPinsMenuModel() const
                {
                    return *m_pMenuModel;
                }

            private:
                MyPinsRepository* m_pMyPinsRepository;
                MyPinsFileIO* m_pMyPinsFileIO;
                MyPinsService* m_pMyPinsService;
                MyPinsWebService* m_pMyPinsWebService;
                MyPinsRepositoryObserver* m_pMyPinsRepositoryObserver;
                IMyPinBoundObjectFactory* m_pMyPinBoundObjectFactory;
                IMyPinBoundObjectRepository* m_pMyPinBoundObjectRepository;
                
                MyPinSelectionHandlerFactory* m_pMyPinsSelectionHandlerFactory;
                MyPinVisibilityStateChangedHandlerFactory* m_pMyPinVisibilityStateChangedHandlerFactory;
                View::MyPinAddedToMenuObserver* m_pMyPinAddedToMenuObserver;
                View::MyPinRemovedFromMenuObserver* m_pMyPinRemovedFromMenuObserver;
                MyPinSelectedMessageHandler* m_pMyPinSelectedMessageHandler;

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
            };
        }
    }
}
