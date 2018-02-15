// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include "CameraTransitions.h"
#include "IAlertBoxFactory.h"
#include "SelectFirstResultSearchService.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "DeepLinkQueryStringParser.h"
#include "DeepLinkConfigHandler.h"
#include "QueryData.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkSearchHandler: public IDeepLinkHandler, private Eegeo::NonCopyable
            {
            public:
                DeepLinkSearchHandler(Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& selectFirstResultSearchService,
                                      Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                      DeepLinkConfigHandler* deepLinkConfigHandlerOrNull);
                
                void HandleDeepLink(const AppInterface::UrlData& data);
                
            private:
                void OnFailAlertBoxDismissed();
                void HandleMapscene(const AppInterface::UrlData& data, const QueryData& queryData);
                
                DeepLinkConfigHandler* m_pDeepLinkConfigHandlerOrNull;
                Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& m_selectFirstResultSearchService;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<DeepLinkSearchHandler> m_failAlertHandler;
            };
        }
    }
}

