// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsSearchResultRefreshService.h"
#include "ISearchResultMyPinsService.h"
#include "ISearchService.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {   
                MyPinsSearchResultRefreshService::MyPinsSearchResultRefreshService(ISearchResultMyPinsService& searchResultMyPinsService,
                                                                                   Search::SdkModel::ISearchService& searchService)
                
                : m_searchResultMyPinsService(searchResultMyPinsService)
                , m_searchService(searchService)
                , m_refreshSearchResultCompletedHandler(this, &MyPinsSearchResultRefreshService::HandleRefreshSearchResultCompleted)
                {
                    
                }
                
                MyPinsSearchResultRefreshService::~MyPinsSearchResultRefreshService()
                {
                    
                }
                
                void MyPinsSearchResultRefreshService::RefreshPinnedSearchResult(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                                                 ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject& searchResultPinBoundObject,
                                                                                 const SearchResultModel& searchResultModel)
                {
                    std::pair<TIdentifierToPinIdMap::iterator, bool> insertVendorIdToPinIdMapping = m_vendorIdToPinMap.insert(std::make_pair(searchResultModel.GetIdentifier(), pinId));
                    
                    Eegeo_ASSERT(insertVendorIdToPinIdMapping.second, "Couldn't add search result ID to pin mapping, key value already exists.\n");
                    
                    std::pair<TPinIdToBoundObjectMap::iterator, bool> insertPinIdToBoundObjectMapping = m_pinIdToSearchResultPinBoundObject.insert(std::make_pair(pinId, &searchResultPinBoundObject));
                    
                    Eegeo_ASSERT(insertPinIdToBoundObjectMapping.second, "Couldn't add pin ID to search pin binding mapping, key value already exists.\n");
                    
                    m_searchService.PerformIdentitySearch(searchResultModel.GetIdentifier(),
                                                          m_refreshSearchResultCompletedHandler);
                }
                
                void MyPinsSearchResultRefreshService::HandleRefreshSearchResultCompleted(const SdkModel::IdentitySearchCallbackData& result)
                {
                    TIdentifierToPinIdMap::iterator identifierToPinIdMapIt(m_vendorIdToPinMap.find(result.GetLocationIdentifier()));
                    Eegeo_ASSERT(identifierToPinIdMapIt != m_vendorIdToPinMap.end());
                    
                    const ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId(identifierToPinIdMapIt->second);
                    
                    TPinIdToBoundObjectMap::iterator pinIdToBoundObjectMapIt(m_pinIdToSearchResultPinBoundObject.find(pinId));
                    Eegeo_ASSERT(pinIdToBoundObjectMapIt != m_pinIdToSearchResultPinBoundObject.end());
                    
                    // Check the pin hasn't been removed from the MyPin repository during our query.
                    if(m_searchResultMyPinsService.ContainsPinWithId(pinId))
                    {
                        ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject& boundObject(*pinIdToBoundObjectMapIt->second);
                        boundObject.FinishRefreshingSearchResult(result.IsSuccess(), result.GetSearchResultModel());
                    }
                    
                    TIdentifierToPinIdMap::size_type numErasedFromIdentifierToPinIdMap = m_vendorIdToPinMap.erase(result.GetLocationIdentifier());
                    Eegeo_ASSERT(numErasedFromIdentifierToPinIdMap == 1);
                   
                    TPinIdToBoundObjectMap::size_type numErasedFromPinIdToBoundObjectMap = m_pinIdToSearchResultPinBoundObject.erase(pinId);
                    Eegeo_ASSERT(numErasedFromPinIdToBoundObjectMap == 1);
                }
            }
        }
    }
}
