// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "IMyPinsService.h"
#include "ISearchResultMyPinsService.h"
#include "SearchResultPoiMyPinService.h"
#include "ISearchResultIconKeyMapper.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {   
            SearchResultPoiMyPinService::SearchResultPoiMyPinService(MyPins::SdkModel::IMyPinsService& myPinsService,
                                                                     Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultMyPinsService,
                                                                     TagSearch::ISearchResultIconKeyMapper& searchResultIconKeyMapper)
            : m_myPinsService(myPinsService)
            , m_searchResultMyPinsService(searchResultMyPinsService)
            , m_searchResultIconKeyMapper(searchResultIconKeyMapper)
            {
                
            }
            
            SearchResultPoiMyPinService::~SearchResultPoiMyPinService()
            {
                
            }
            
            void SearchResultPoiMyPinService::AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult)
            {
                MyPins::SdkModel::MyPinModel myPinModel;
                
                if(m_searchResultMyPinsService.TryGetPinForSearchResult(searchResult, myPinModel))
                {
                    // The pin already exists, so remove it and return!
                    m_myPinsService.RemovePinWithId(myPinModel.Identifier());
                }
                else
                {
                    // The pin doesn't exist, so we must add it...
                    const std::string& pinIconKey = m_searchResultIconKeyMapper.GetIconKeyFromSearchResult(searchResult);
                    m_myPinsService.SaveSearchResultPoiPin(searchResult, pinIconKey);
                }
            }
        }
    }
}
