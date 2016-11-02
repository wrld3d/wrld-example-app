// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionMenuGeoNamesResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuGeoNamesResponseReceivedMessage::DirectionMenuGeoNamesResponseReceivedMessage(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& results):
        m_searchResults(results)
        {
            
        }
        
        const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& DirectionMenuGeoNamesResponseReceivedMessage::SearchResults() const
        {
            return m_searchResults;
        }
        
    }
}
