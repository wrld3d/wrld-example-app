// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionMenuGeoNamesResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuGeoNamesResponseReceivedMessage::DirectionMenuGeoNamesResponseReceivedMessage(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& results, bool   isStartLocationActive):
            m_searchResults(results)
        , m_isStartLocationActive(isStartLocationActive)
        {
            
        }
        
        const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& DirectionMenuGeoNamesResponseReceivedMessage::SearchResults() const
        {
            return m_searchResults;
        }
        
        bool DirectionMenuGeoNamesResponseReceivedMessage::IsStartLocationActive() const
        {
            return m_isStartLocationActive;
        }
        
    }
}
