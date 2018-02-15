// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkSearchHandler.h"
#include <vector>
#include "StringHelpers.h"
#include "DeepLinkQueryStringParser.h"
#include "QueryData.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkSearchHandler::DeepLinkSearchHandler(Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& selectFirstResultSearchService,
                                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                         DeepLinkConfigHandler* deepLinkConfigHandlerOrNull)
            : m_selectFirstResultSearchService(selectFirstResultSearchService)
            , m_failAlertHandler(this, &DeepLinkSearchHandler::OnFailAlertBoxDismissed)
            , m_pDeepLinkConfigHandlerOrNull(deepLinkConfigHandlerOrNull)
            {
            }
            
            void DeepLinkSearchHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                const QueryData& queryData = DeepLinkQueryStringParser().ParseData(data.query);
                if(queryData.HasMapscene())
                {
                    HandleMapscene(data, queryData);
                }
                
                m_selectFirstResultSearchService.PerformSearch(queryData.GetQuery(), queryData.GetIndoorId());
            }
            
            void DeepLinkSearchHandler::HandleMapscene(const AppInterface::UrlData& data, const QueryData& queryData)
            {
                if(m_pDeepLinkConfigHandlerOrNull != nullptr)
                {
                    const std::string path = "/" + queryData.GetMapscene();
                    m_pDeepLinkConfigHandlerOrNull->LoadMapscene(path, true);
                }
            }
            
            void DeepLinkSearchHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}

