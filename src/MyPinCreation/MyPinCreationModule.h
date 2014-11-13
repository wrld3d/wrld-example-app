// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IMyPinCreationModule.h"
#include "Modules.h"
#include "VectorMathDecl.h"
#include "Camera.h"
#include "Rendering.h"
#include "Terrain.h"
#include "IIdentity.h"
#include "SearchResultMenu.h"
#include "Menu.h"
#include "Search.h"
#include "IdTypes.h"
#include "MyPins.h"
#include "MyPinCreationModelObserver.h"
#include "MyPinCreationViewStateChangedHandler.h"
#include "MyPinCreationViewSavePinHandler.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationModule : public IMyPinCreationModule
        {
        public:
            MyPinCreationModule(MyPins::IMyPinsService& myPinsService,
                              Eegeo::Helpers::IIdentityProvider& identityProvider,
                              ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                              ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                              ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                              ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel,
                                ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                                ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinCreationModule();
            
            IMyPinCreationModel& GetMyPinCreationModel() const;
            IMyPinCreationInitiationViewModel& GetMyPinCreationInitiationViewModel() const;
            IMyPinCreationConfirmationViewModel& GetMyPinCreationConfirmationViewModel() const;
            IMyPinCreationCompositeViewModel& GetMyPinCreationCompositeViewModel() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetInitiationScreenControlViewModel() const;
            ScreenControlViewModel::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const;
            
        private:
    
            MyPinCreationModel* m_pMyPinCreationModel;
            MyPinCreationInitiationViewModel* m_pMyPinCreationInitiationViewModel;
            MyPinCreationConfirmationViewModel* m_pMyPinCreationConfirmationViewModel;
            MyPinCreationCompositeViewModel* m_pMyPinCreationCompositeViewModel;
            MyPinCreationModelObserver* m_pMyPinCreationModelObserver;
            MyPinCreationViewStateChangedHandler* m_pMyPinCreationViewStateChangedHandler;
            MyPinCreationViewSavePinHandler* m_pMyPinCreationViewSavePinHandler;
        };
    }
}