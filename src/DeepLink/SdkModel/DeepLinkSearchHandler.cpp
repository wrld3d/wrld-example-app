// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkSearchHandler.h"
#include <vector>
#include "StringHelpers.h"
#include "LatLongAltitude.h"

namespace
{
    std::string DEFAULT_INDOOR_ID = "";
    
    const size_t SEARCH_INDEX = 1;
    const size_t INDOOR_INDEX = 2;
    
}

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkSearchHandler::DeepLinkSearchHandler(Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& selectFirstResultSearchService,
                                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
            : m_selectFirstResultSearchService(selectFirstResultSearchService)
            , m_failAlertHandler(this, &DeepLinkSearchHandler::OnFailAlertBoxDismissed)
            {
            }
            
            void DeepLinkSearchHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                std::vector<std::string> parts;
                size_t numParts = Eegeo::Helpers::Split(data.path, '/', parts);
                Eegeo::Space::LatLong latLon(0, 0);
                
                
                std::string& queryString = parts.at(SEARCH_INDEX);
                if(numParts > INDOOR_INDEX)
                {
                    std::string& indoorId = parts.at(INDOOR_INDEX);
                    m_selectFirstResultSearchService.HandleSearch(queryString, indoorId);
                }
                else
                {
                    m_selectFirstResultSearchService.HandleSearch(queryString);
                }
            }
            
            void DeepLinkSearchHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}

