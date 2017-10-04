// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMyPinsService.h"
#include "SearchResultModel.h"
#include "IMyPinsRepository.h"
#include "MyPinModel.h"

using Eegeo::Helpers::ICallback1;
using ExampleApp::Search::SdkModel::SearchResultModel;

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {
                SearchResultMyPinsService::SearchResultMyPinsService(ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus)
                : m_sdkModelDomainEventBus(sdkModelDomainEventBus)
                , m_searchResultPinAddedEventHandler(this, &SearchResultMyPinsService::OnSearchResultPinAddedEvent)
                , m_searchResultPinRemovedEventHandler(this, &SearchResultMyPinsService::OnSearchResultPinRemovedEvent)
                {
                    m_sdkModelDomainEventBus.Subscribe(m_searchResultPinAddedEventHandler);
                    m_sdkModelDomainEventBus.Subscribe(m_searchResultPinRemovedEventHandler);
                }
                
                SearchResultMyPinsService::~SearchResultMyPinsService()
                {
                    m_sdkModelDomainEventBus.Unsubscribe(m_searchResultPinRemovedEventHandler);
                    m_sdkModelDomainEventBus.Unsubscribe(m_searchResultPinAddedEventHandler);
                }
                
                bool SearchResultMyPinsService::IsSearchResultPinned(const SearchResultModel& searchResult) const
                {
                    return m_searchResultToPinId.find(searchResult) != m_searchResultToPinId.end();
                }
                
                bool SearchResultMyPinsService::TryGetPinForSearchResult(const Search::SdkModel::SearchResultModel& searchResult,
                                                                         ExampleApp::MyPins::SdkModel::MyPinModel& out_myPinModel) const
                {
                    TSearchResultToPinIdMap::const_iterator it = m_searchResultToPinId.find(searchResult);
                    
                    if(it != m_searchResultToPinId.end())
                    {
                        out_myPinModel = it->second;
                        return true;
                    }
                    
                    return false;
                }

                bool SearchResultMyPinsService::TryGetPinTitleForSearchResultIdentifier(const std::string& identifier,
                                                                                        std::string& out_pinTitle) const
                {
                    for (TSearchResultToPinIdMap::const_iterator it = m_searchResultToPinId.begin();
                        it != m_searchResultToPinId.end();
                        ++it)
                    {
                        if (it->first.GetIdentifier() == identifier)
                        {
                            out_pinTitle = it->second.GetTitle();
                            return true;
                        }
                    }

                    return false;
                }
                
                bool SearchResultMyPinsService::ContainsPinWithId(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId) const
                {
                    for(TSearchResultToPinIdMap::const_iterator it = m_searchResultToPinId.begin();
                        it != m_searchResultToPinId.end();
                        ++ it)
                    {
                        if(it->second.Identifier() == pinId)
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                void SearchResultMyPinsService::InsertSearchResultPinnedCallback(ICallback1<SearchResultModel>& callback)
                {
                    m_searchResultPinnedCallbacks.AddCallback(callback);
                }
                
                void SearchResultMyPinsService::RemoveSearchResultPinnedCallback(ICallback1<SearchResultModel>& callback)
                {
                    m_searchResultPinnedCallbacks.RemoveCallback(callback);
                }
                
                void SearchResultMyPinsService::InsertSearchResultUnpinnedCallback(ICallback1<SearchResultModel>& callback)
                {
                    m_searchResultUnpinnedCallbacks.AddCallback(callback);
                }
                
                void SearchResultMyPinsService::RemoveSearchResultUnpinnedCallback(ICallback1<SearchResultModel>& callback)
                {
                    m_searchResultUnpinnedCallbacks.RemoveCallback(callback);
                }
                
                void SearchResultMyPinsService::OnSearchResultPinAddedEvent(const ExampleApp::MyPins::SdkModel::SearchResultPinAddedEvent& event)
                {
                    Search::SdkModel::SearchResultModel searchResultModel(event.GetSearchResultModel());
                    
                    std::pair<TSearchResultToPinIdMap::iterator, bool> insertSearchResultToPinIdResult = m_searchResultToPinId.insert(std::make_pair(searchResultModel, event.GetMyPinModel()));
                    
                    Eegeo_ASSERT(insertSearchResultToPinIdResult.second, "Couldn't add SearchResultToPinId mapping, key value already exists.\n");
                    
                    m_searchResultPinnedCallbacks.ExecuteCallbacks(searchResultModel);
                }
                
                void SearchResultMyPinsService::OnSearchResultPinRemovedEvent(const ExampleApp::MyPins::SdkModel::SearchResultPinRemovedEvent& event)
                {
                    Search::SdkModel::SearchResultModel searchResultModel(event.GetSearchResultModel());
                    
                    m_searchResultUnpinnedCallbacks.ExecuteCallbacks(searchResultModel);
                    
                    TSearchResultToPinIdMap::size_type numErasedSearchResultToPinIdResult = m_searchResultToPinId.erase(searchResultModel);
                    
                    Eegeo_ASSERT(numErasedSearchResultToPinIdResult == 1, "Couldn't remove SearchResultToPinId binding, key value not present.\n");
                }
            }
        }
    }
}
