// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "UiToNativeMessageBus.h"
#include "IConnectivityService.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class MyPinCreationDetailsViewModule : public IMyPinCreationDetailsViewModule
        {
        public:
            MyPinCreationDetailsViewModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                           IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                           Eegeo::Web::IConnectivityService& connectivityService,
                                           UIViewController* rootViewController);
            
            ~MyPinCreationDetailsViewModule();
            
            MyPinCreationDetailsViewController& GetMyPinCreationDetailsViewController() const;
            MyPinCreationDetailsView& GetMyPinCreationDetailsView() const;
        
        private:
            MyPinCreationDetailsViewController* m_pController;
        };
    }
}