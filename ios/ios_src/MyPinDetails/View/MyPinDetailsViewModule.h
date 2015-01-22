// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "IMyPinDetailsViewModule.h"
#include "BidirectionalBus.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsViewModule: public IMyPinDetailsViewModule, private Eegeo::NonCopyable
            {
            private:
                MyPinDetailsView* m_pView;
                MyPinDetailsController* m_pController;

            public:
                MyPinDetailsViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                       IMyPinDetailsViewModel& MyPinDetailsViewModel,
                                       const Eegeo::Rendering::ScreenProperties& screenProperties);

                ~MyPinDetailsViewModule();

                MyPinDetailsController& GetMyPinDetailsController() const;
                MyPinDetailsView& GetMyPinDetailsView() const;
            };
        }
    }
}
