// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DeepLinkModel.h"
#include "ApplicationConfiguration.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkController
            {
            public:
                DeepLinkController(DeepLinkModel& deepLinkModel,
                                   ExampleAppMessaging::TMessageBus& messageBus);
                ~DeepLinkController();
                void HandleDeepLinkOpen(const AppInterface::UrlData& data);
            private:
                DeepLinkModel& m_deepLinkModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
