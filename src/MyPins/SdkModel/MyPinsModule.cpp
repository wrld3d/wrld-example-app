// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsModule.h"
#include "Types.h"
#include "MyPinsRepository.h"
#include "MyPinsFileIO.h"
#include "MyPinsService.h"
#include "MyPinsRepositoryObserver.h"
#include "LatLongAltitude.h"
#include "IPlatformAbstractionModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MyPinSelectionHandlerFactory.h"
#include "MyPinAddedToMenuObserver.h"
#include "MyPinRemovedFromMenuObserver.h"
#include "MyPinSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsModule::MyPinsModule(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                       Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                       PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                       Menu::View::IMenuViewModel& menuViewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
                : m_pMyPinsRepository(NULL)
                , m_pMyPinsFileIO(NULL)
                , m_pMyPinsService(NULL)
                , m_pMyPinsRepositoryObserver(NULL)
                , m_pMenuModel(NULL)
                , m_pMenuOptionsModel(NULL)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                m_pMyPinsRepository = Eegeo_NEW(MyPinsRepository)();

                m_pMyPinsSelectionHandlerFactory = Eegeo_NEW(MyPinSelectionHandlerFactory)(messageBus);

                m_pMyPinsFileIO = Eegeo_NEW(MyPinsFileIO)(platformAbstractions.GetFileIO(), persistentSettings);

                m_pMyPinsRepositoryObserver = Eegeo_NEW(MyPinsRepositoryObserver)(*m_pMyPinsRepository,
                                              *m_pMyPinsFileIO,
                                              messageBus);


                m_pMyPinAddedToMenuObserver = Eegeo_NEW(View::MyPinAddedToMenuObserver)(menuViewModel,
                                              *m_pMenuOptionsModel,
                                              messageBus);

                m_pMyPinRemovedFromMenuObserver = Eegeo_NEW(View::MyPinRemovedFromMenuObserver)(*m_pMenuOptionsModel,
                                                  messageBus);

                m_pMyPinsService = Eegeo_NEW(MyPinsService)(*m_pMyPinsRepository,
                                   *m_pMyPinsFileIO,
                                   *m_pMyPinsSelectionHandlerFactory,
                                   worldPinsService,
                                   platformAbstractions.GetWebLoadRequestFactory());
                m_pMyPinSelectedMessageHandler = Eegeo_NEW(MyPinSelectedMessageHandler)(cameraTransitionController,
                                                 messageBus);

            }

            MyPinsModule::~MyPinsModule()
            {
                Eegeo_DELETE m_pMyPinSelectedMessageHandler;
                Eegeo_DELETE m_pMyPinsService;

                Eegeo_DELETE m_pMyPinRemovedFromMenuObserver;
                Eegeo_DELETE m_pMyPinAddedToMenuObserver;

                Eegeo_DELETE m_pMyPinsFileIO;

                Eegeo_DELETE m_pMyPinsSelectionHandlerFactory;
                Eegeo_DELETE m_pMyPinsRepositoryObserver;
                Eegeo_DELETE m_pMyPinsRepository;

                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }

            IMyPinsService& MyPinsModule::GetMyPinsService() const
            {
                return *m_pMyPinsService;
            }
        }
    }
}
