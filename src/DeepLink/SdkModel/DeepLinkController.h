// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DeepLinkModel.h"
#include "DeepLinkRequest.h"
#include "ApplicationConfiguration.h"



namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkController: private Eegeo::NonCopyable
            {
                DeepLinkModel& m_deepLinkModel;
                DeepLinkRequest* m_pDelayedRequest;
                bool m_uiStarted;
            public:
                DeepLinkController(DeepLinkModel& deepLinkModel);
                ~DeepLinkController();
                void OnUiStarted();
                void HandleDeepLinkOpen(const AppInterface::UrlData& data);
            private:
                void DoHandleDeepLinkOpen(const AppInterface::UrlData& data);
            };
        }
    }
}
