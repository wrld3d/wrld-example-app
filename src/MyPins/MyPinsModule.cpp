// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
        MyPinsModule::MyPinsModule(WorldPins::IWorldPinsService& worldPinsService,
                                   Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                   PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                   ExampleApp::Menu::IMenuViewModel& menuViewModel,
                                   ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                   ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                                   CameraTransitions::ICameraTransitionController& cameraTransitionController)
        : m_pMyPinsRepository(NULL)
        , m_pMyPinsFileIO(NULL)
        , m_pMyPinsService(NULL)
        , m_pMyPinsRepositoryObserver(NULL)
        , m_pMenuModel(NULL)
        , m_pMenuOptionsModel(NULL)
        {
            m_pMenuModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pMenuModel);
            
            m_pMyPinsRepository = Eegeo_NEW(MyPinsRepository)();

            m_pMyPinsSelectionHandlerFactory = Eegeo_NEW(MyPinSelectionHandlerFactory)(nativeToUiMessageBus);
            
            m_pMyPinsFileIO = Eegeo_NEW(MyPinsFileIO)(platformAbstractions.GetFileIO(), persistentSettings);
            
            m_pMyPinsRepositoryObserver = Eegeo_NEW(MyPinsRepositoryObserver)(*m_pMyPinsRepository,
                                                                              *m_pMyPinsFileIO,
                                                                              nativeToUiMessageBus);

            
            m_pMyPinAddedToMenuObserver = Eegeo_NEW(MyPinAddedToMenuObserver)(menuViewModel,
            																  *m_pMenuOptionsModel,
            																  uiToNativeMessageBus,
            																  nativeToUiMessageBus);
            
            m_pMyPinRemovedFromMenuObserver = Eegeo_NEW(MyPinRemovedFromMenuObserver)(*m_pMenuOptionsModel,
                                                                                      nativeToUiMessageBus);
            
            m_pMyPinsService = Eegeo_NEW(MyPinsService)(*m_pMyPinsRepository,
                                                        *m_pMyPinsFileIO,
                                                        *m_pMyPinsSelectionHandlerFactory,
                                                        worldPinsService,
                                                        platformAbstractions.GetWebLoadRequestFactory());
            m_pMyPinSelectedMessageHandler = Eegeo_NEW(MyPinSelectedMessageHandler)(cameraTransitionController,
                                                                                    uiToNativeMessageBus);
            
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
