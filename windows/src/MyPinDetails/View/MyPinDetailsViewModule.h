// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinDetailsViewModule.h"
#include "MyPinDetailsViewIncludes.h"
#include "WindowsNativeState.h"
#include "MyPinDetails.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsViewModule : public IMyPinDetailsViewModule
            {
            public:
                MyPinDetailsViewModule(
                    WindowsNativeState& nativeState,
                    IMyPinDetailsViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus);
                ~MyPinDetailsViewModule();

            private:

                MyPinDetailsView* m_pView;
                MyPinDetailsController* m_pController;
            };
        }
    }
}
