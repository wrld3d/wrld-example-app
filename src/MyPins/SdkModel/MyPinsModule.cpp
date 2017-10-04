// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsModule.h"
#include "Types.h"
#include "MyPinsRepository.h"
#include "MyPinBoundObjectRepository.h"
#include "MyPinBoundObjectFactory.h"
#include "MyPinsRepository.h"
#include "MyPinsFileIO.h"
#include "MyPinsService.h"
#include "MyPinsRepositoryObserver.h"
#include "LatLongAltitude.h"
#include "IPlatformAbstractionModule.h"
#include "SortedMenuModel.h"
#include "SortedMenuComparisonFunctions.h"
#include "MenuOptionsModel.h"
#include "MyPinSelectionHandlerFactory.h"
#include "MyPinAddedToMenuObserver.h"
#include "MyPinRemovedFromMenuObserver.h"
#include "MyPinSelectedMessageHandler.h"
#include "MyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPinsWebService.h"

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
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                       Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                       Metrics::IMetricsService& metricsService,
                                       const std::string& myPinsWebServiceUrl,
                                       const std::string& myPinsWebServiceAuthToken,
                                       const std::string& myPinsPoiSetId,
                                       const Menu::View::IMenuReactionModel& menuReaction,
                                       Menu::View::IMenuIgnoredReactionModel& ignoredMenuReaction)
                : m_pMyPinsRepository(NULL)
                , m_pMyPinsFileIO(NULL)
                , m_pMyPinsService(NULL)
                , m_pMyPinsRepositoryObserver(NULL)
                , m_pMenuModel(NULL)
                , m_pMenuOptionsModel(NULL)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::SortedMenuModel)(Menu::View::LexicographicalNameCompare);
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                m_pMyPinsRepository = Eegeo_NEW(MyPinsRepository)();
                
                m_pMyPinsWebService = Eegeo_NEW(MyPinsWebService)(myPinsWebServiceUrl,
                                                                  myPinsWebServiceAuthToken,
                                                                  myPinsPoiSetId,
                                                                  platformAbstractions.GetWebLoadRequestFactory());
                
                m_pMyPinBoundObjectRepository = Eegeo_NEW(MyPinBoundObjectRepository);
                
                m_pMyPinBoundObjectFactory = Eegeo_NEW(MyPinBoundObjectFactory)(messageBus,
                                                                                sdkModelDomainEventBus,
                                                                                myPinsSearchResultRefreshService,
                                                                                *m_pMyPinsWebService);

                m_pMyPinsSelectionHandlerFactory = Eegeo_NEW(MyPinSelectionHandlerFactory)(*m_pMyPinBoundObjectRepository, metricsService);
                
                m_pMyPinVisibilityStateChangedHandlerFactory = Eegeo_NEW(MyPinVisibilityStateChangedHandlerFactory)(*m_pMyPinBoundObjectRepository);

                m_pMyPinsFileIO = Eegeo_NEW(MyPinsFileIO)(platformAbstractions.GetFileIO(),
                                                          persistentSettings,
                                                          *m_pMyPinBoundObjectFactory,
                                                          *m_pMyPinBoundObjectRepository);
                
                m_pMyPinsRepositoryObserver = Eegeo_NEW(MyPinsRepositoryObserver)(*m_pMyPinsRepository,
                                                                                  *m_pMyPinBoundObjectRepository,
                                                                                  *m_pMyPinsFileIO,
                                                                                  messageBus);
                
                m_pMyPinAddedToMenuObserver = Eegeo_NEW(View::MyPinAddedToMenuObserver)(menuViewModel,
                                                                                        *m_pMenuOptionsModel,
                                                                                        messageBus,
                                                                                        menuReaction,
                                                                                        ignoredMenuReaction);
                
                m_pMyPinRemovedFromMenuObserver = Eegeo_NEW(View::MyPinRemovedFromMenuObserver)(*m_pMenuOptionsModel,
                                                  messageBus);

                m_pMyPinsService = Eegeo_NEW(MyPinsService)(*m_pMyPinsRepository,
                                                            *m_pMyPinsFileIO,
                                                            *m_pMyPinsSelectionHandlerFactory,
                                                            *m_pMyPinVisibilityStateChangedHandlerFactory,
                                                            *m_pMyPinBoundObjectFactory,
                                                            *m_pMyPinBoundObjectRepository,
                                                            worldPinsService,
                                                            messageBus);
                
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

                Eegeo_DELETE m_pMyPinVisibilityStateChangedHandlerFactory;
                Eegeo_DELETE m_pMyPinsSelectionHandlerFactory;
                Eegeo_DELETE m_pMyPinsRepositoryObserver;
                
                Eegeo_DELETE m_pMyPinBoundObjectFactory;
                Eegeo_DELETE m_pMyPinBoundObjectRepository;
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
