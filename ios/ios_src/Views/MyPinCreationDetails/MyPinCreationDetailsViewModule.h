// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class MyPinCreationDetailsViewModule : public IMyPinCreationDetailsViewModule
        {
        public:
            MyPinCreationDetailsViewModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                           IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel);
            
            ~MyPinCreationDetailsViewModule();
            
            MyPinCreationDetailsViewController& GetMyPinCreationDetailsViewController() const;
            MyPinCreationDetailsView& GetMyPinCreationDetailsView() const;
        
        private:
            MyPinCreationDetailsViewController* m_pController;
        };
    }
}