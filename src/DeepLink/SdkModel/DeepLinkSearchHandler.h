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
#include "MapsceneLoader.h"

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
                                      Mapscene::SdkModel::MapsceneLoader& mapsceneLoader);
                
                void HandleDeepLink(const AppInterface::UrlData& data);
                
            private:
                void OnFailAlertBoxDismissed();
                void HandleMapscene(const AppInterface::UrlData& data, const QueryData& queryData);
                
                Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& m_selectFirstResultSearchService;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<DeepLinkSearchHandler> m_failAlertHandler;
                Mapscene::SdkModel::MapsceneLoader& m_mapsceneLoader;
            };
        }
    }
}

