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
#include "MyPinSelectionHandlerFactory.h"
#include "MyPinAddedToMenuObserver.h"
#include "MyPinRemovedFromMenuObserver.h"
#include "MyPinSelectedMessageHandler.h"
#include "MyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPinsWebService.h"
#include "MyPinMenuOption.h"
#include "MyPinSelectedMessageHandler.h"
#include "IWebLoadRequestFactory.h"
#include "IMyPinSsearchResultRefreshService.h"
#include "IPersistentSettingsModel.h"
#include "IWorldPinsService.h"
#include "ICameraTransitionController.h"
#include "ModalityIgnoredReactionModel.h"
#include "MyPinsLoadingMessageHandler.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            void MyPinsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<View::MyPinsMenuModel>().singleInstance();
                builder->registerType<View::MyPinsMenuOptionsModel>().singleInstance();
                builder->registerType<MyPinsRepository>().as<IMyPinsRepository>().singleInstance();
                builder->registerType<MyPinsWebService>().singleInstance();
                builder->registerType<MyPinBoundObjectRepository>().as<IMyPinBoundObjectRepository>().singleInstance();
                builder->registerType<MyPinBoundObjectFactory>().as<IMyPinBoundObjectFactory>().singleInstance();
                builder->registerType<MyPinSelectionHandlerFactory>().as<IMyPinSelectionHandlerFactory>().singleInstance();
                builder->registerType<MyPinVisibilityStateChangedHandlerFactory>().as<IMyPinVisibilityStateChangedHandlerFactory>().singleInstance();
                builder->registerType<MyPinsFileIO>().singleInstance();
                builder->registerType<MyPinsRepositoryObserver>().singleInstance();
                builder->registerType<View::MyPinAddedToMenuObserver>().singleInstance();
                builder->registerType<MyPinsService>().as<IMyPinsService>().singleInstance();
                builder->registerType<MyPinSelectedMessageHandler>().singleInstance();
                builder->registerType<MyPinsLoadingMessageHandler>().singleInstance();
            }
            
            void MyPinsModule::RegisterLeaves()
            {
                RegisterLeaf<MyPinsLoadingMessageHandler>();
                RegisterLeaf<MyPinSelectedMessageHandler>();
                RegisterLeaf<View::MyPinAddedToMenuObserver>();
                RegisterLeaf<MyPinsRepositoryObserver>();
            }
        }
    }
}
