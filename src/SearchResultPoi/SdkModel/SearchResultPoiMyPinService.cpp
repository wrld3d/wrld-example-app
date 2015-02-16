// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "SearchResultPoiMyPinService.h"
#include "IMyPinsService.h"
#include "IMyPinsRepository.h"
#include "ISearchResultIconCategoryMapper.h"
#include "MyPinsSearchResultExtensions.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {   
            SearchResultPoiMyPinService::SearchResultPoiMyPinService(MyPins::SdkModel::IMyPinsService& myPinsService,
                                                                     MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                                                     CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper)
            : m_myPinsService(myPinsService)
            , m_myPinsRepository(myPinsRepository)
            , m_searchResultIconCategoryMapper(searchResultIconCategoryMapper)
            {
                
            }
            
            SearchResultPoiMyPinService::~SearchResultPoiMyPinService()
            {
                
            }
            
            void SearchResultPoiMyPinService::AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult)
            {
                MyPins::SdkModel::MyPinModel* pMyPinModel = NULL;
                
                if(TryFindPinnedPoiForSearchResult(m_myPinsRepository, searchResult, pMyPinModel))
                {
                    // The pin already exists, so remove it and return!
                    m_myPinsService.RemovePinWithId(pMyPinModel->Identifier());
                }
                else
                {
                    // The pin doesn't exist, so we must add it...
                    const int pinIconIndex = m_searchResultIconCategoryMapper.GetIconIndexFromSearchResult(searchResult);
                    m_myPinsService.SaveSearchResultPoiPin(searchResult, pinIconIndex);
                }
            }
        }
    }
}
