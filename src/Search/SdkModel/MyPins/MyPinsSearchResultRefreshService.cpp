// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsSearchResultRefreshService.h"
#include "ISearchResultMyPinsService.h"
#include "ISearchService.h"
#include "SearchResultModel.h"
#include "Logger.h"

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
                    
                    if(!insertVendorIdToPinIdMapping.second)
                    {
                        // We have been unable to add the pin to the m_vendorIdToPinMap -- this suggests we are already performing a
                        // refresh for this vendor. Possible causes are that the last refresh is taking a very long time, or that
                        // we have unpinned and pinned the same result and are somehow refreshing immediately.
                        //
                        // If this is the case it implies that our current in-flight refresh for this pin is bound to an invalid object,
                        // which will be discovered in HandleRefreshSearchResultCompleted (if this is the case there will be no pin
                        // with the TPinModelId in m_searchResultMyPinsService, so the stale bound object will be discarded and not
                        // used).
                        //
                        // What we should do is "hi-jack" this in-flight refresh, binding it to the new pin. This is safe, as it is
                        // invalid to pin the same object (as defined by object identity) more than once at a time. There is no
                        // race condition as the SDKModel operations are all running on the same thread (the async request joins
                        // before triggering the callback).
                        
                        EXAMPLE_LOG("Couldn't add search result ID to pin mapping, key value %s already exists.\n",
                                    searchResultModel.GetIdentifier().c_str());
                        
                        TIdentifierToPinIdMap::iterator identifierToPinIdMapIt(m_vendorIdToPinMap.find(searchResultModel.GetIdentifier()));
                        Eegeo_ASSERT(identifierToPinIdMapIt != m_vendorIdToPinMap.end());
                        
                        const ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType existingPinId(identifierToPinIdMapIt->second);
                        
                        Eegeo_ASSERT(!m_searchResultMyPinsService.ContainsPinWithId(existingPinId),
                                     "More than one search result pin with same ID %s exists, this should not be possible.\n",
                                     searchResultModel.GetIdentifier().c_str());
                        
                        // Erase the old pinId and bound object for this search result, and add the new one.
                        TIdentifierToPinIdMap::size_type numErasedFromIdentifierToPinIdMap = m_vendorIdToPinMap.erase(searchResultModel.GetIdentifier());
                        Eegeo_ASSERT(numErasedFromIdentifierToPinIdMap == 1);
                        
                        TPinIdToBoundObjectMap::size_type numErasedFromPinIdToBoundObjectMap = m_pinIdToSearchResultPinBoundObject.erase(existingPinId);
                        Eegeo_ASSERT(numErasedFromPinIdToBoundObjectMap == 1);
                        
                        std::pair<TIdentifierToPinIdMap::iterator, bool> insertVendorIdToPinIdMappingSecondTry = m_vendorIdToPinMap.insert(std::make_pair(searchResultModel.GetIdentifier(), pinId));
                        
                        Eegeo_ASSERT(insertVendorIdToPinIdMappingSecondTry.second);
                        
                        std::pair<TPinIdToBoundObjectMap::iterator, bool> insertPinIdToBoundObjectMapping = m_pinIdToSearchResultPinBoundObject.insert(std::make_pair(pinId, &searchResultPinBoundObject));
                        
                        Eegeo_ASSERT(insertPinIdToBoundObjectMapping.second);
                    }
                    else
                    {
                        // We successfully inserted a pin model for the pinned search result, we now insert its bound object so that we can
                        // call it back when the request is complete and the search result model can be refreshed. This should succeed,
                        // as there should be no bound object for this pin ID if we were able to insert the place ID -- otherwise, this would
                        // imply the same place is pinned twice which is invalid.
                        //
                        // After checking this we dispatch the request. We inspect the state in these maps in the request callback,
                        // HandleRefreshSearchResultCompleted -- in here we must verify the pinned result still exists by checking the
                        // pin ID.
                        
                        std::pair<TPinIdToBoundObjectMap::iterator, bool> insertPinIdToBoundObjectMapping = m_pinIdToSearchResultPinBoundObject.insert(std::make_pair(pinId, &searchResultPinBoundObject));
                        
                        Eegeo_ASSERT(insertPinIdToBoundObjectMapping.second,
                                     "Couldn't add pin ID to search pin binding mapping, key value already exists.\n");
                        
                        m_searchService.PerformIdentitySearch(searchResultModel,
                                                              m_refreshSearchResultCompletedHandler);
                    }
                }
                
                void MyPinsSearchResultRefreshService::HandleRefreshSearchResultCompleted(const SdkModel::IdentitySearchCallbackData& result)
                {
                    TIdentifierToPinIdMap::iterator identifierToPinIdMapIt(m_vendorIdToPinMap.find(result.GetLocationIdentifier()));
                    if(identifierToPinIdMapIt == m_vendorIdToPinMap.end())
                    {
                        Eegeo_TTY("couldn't find the PinId that maps to the result's locationId");
                        return;
                    }
                    
                    const ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId(identifierToPinIdMapIt->second);
                    
                    TPinIdToBoundObjectMap::iterator pinIdToBoundObjectMapIt(m_pinIdToSearchResultPinBoundObject.find(pinId));
                    if(pinIdToBoundObjectMapIt == m_pinIdToSearchResultPinBoundObject.end())
                    {
                        Eegeo_TTY("couldn't find the bound search result that maps to the PinId");
                        return;
                    }
                    
                    // Check the pin hasn't been removed from the MyPin repository during our query.
                    if(m_searchResultMyPinsService.ContainsPinWithId(pinId))
                    {
                        ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject& boundObject(*pinIdToBoundObjectMapIt->second);
                        boundObject.FinishRefreshingSearchResult(result.IsSuccess(), pinId, result.GetSearchResultModel());
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
