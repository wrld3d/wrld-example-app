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
                                                         Mapscene::SdkModel::MapsceneLoader& mapsceneLoader)
            : m_selectFirstResultSearchService(selectFirstResultSearchService)
            , m_failAlertHandler(this, &DeepLinkSearchHandler::OnFailAlertBoxDismissed)
            , m_mapsceneLoader(mapsceneLoader)
            {
            }
            
            void DeepLinkSearchHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                const QueryData& queryData = DeepLinkQueryStringParser().ParseData(data);
                if(queryData.HasMapscene())
                {
                    HandleMapscene(data, queryData);
                }

                if(queryData.HasQuery())
                {
                    m_selectFirstResultSearchService.PerformSearch(queryData.GetQuery(),
                                                                   queryData.GetIndoorId());
                }
            }
            
            void DeepLinkSearchHandler::HandleMapscene(const AppInterface::UrlData& data, const QueryData& queryData)
            {
                const std::string path = "/" + queryData.GetMapscene();
                m_mapsceneLoader.LoadMapscene(path, true);
            }
            
            void DeepLinkSearchHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}

