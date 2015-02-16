// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapMyPinsService.h"
#include "SearchResultModel.h"
#include "IMyPinsRepository.h"
#include "MyPinModel.h"
#include "MyPinsSearchResultExtensions.h"

using Eegeo::Helpers::ICallback1;
using ExampleApp::MyPins::SdkModel::IMyPinsRepository;
using ExampleApp::Search::SdkModel::SearchResultModel;

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            SearchResultOnMapMyPinsService::SearchResultOnMapMyPinsService(IMyPinsRepository& myPinsRepository)
            : m_myPinsRepository(myPinsRepository)
            , m_pinAddedCallback(this, &SearchResultOnMapMyPinsService::HandlePinAdded)
            , m_pinRemovedCallback(this, &SearchResultOnMapMyPinsService::HandlePinRemoved)
            {
                m_myPinsRepository.InsertItemAddedCallback(m_pinAddedCallback);
                m_myPinsRepository.InsertItemRemovedCallback(m_pinRemovedCallback);
            }
            
            SearchResultOnMapMyPinsService::~SearchResultOnMapMyPinsService()
            {
                m_myPinsRepository.RemoveItemRemovedCallback(m_pinRemovedCallback);
                m_myPinsRepository.RemoveItemAddedCallback(m_pinAddedCallback);
            }
            
            bool SearchResultOnMapMyPinsService::IsSearchResultPinned(const SearchResultModel& searchResult) const
            {
                MyPins::SdkModel::MyPinModel* pMyPinModel = NULL;
                
                if(TryFindPinnedPoiForSearchResult(m_myPinsRepository, searchResult, pMyPinModel))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            
            void SearchResultOnMapMyPinsService::InsertSearchResultPinnedCallback(ICallback1<SearchResultModel>& callback)
            {
                m_searchResultPinnedCallbacks.AddCallback(callback);
            }
            
            void SearchResultOnMapMyPinsService::RemoveSearchResultPinnedCallback(ICallback1<SearchResultModel>& callback)
            {
                m_searchResultPinnedCallbacks.RemoveCallback(callback);
            }
            
            void SearchResultOnMapMyPinsService::InsertSearchResultUnpinnedCallback(ICallback1<SearchResultModel>& callback)
            {
                m_searchResultUnpinnedCallbacks.AddCallback(callback);
            }
            
            void SearchResultOnMapMyPinsService::RemoveSearchResultUnpinnedCallback(ICallback1<SearchResultModel>& callback)
            {
                m_searchResultUnpinnedCallbacks.RemoveCallback(callback);
            }
            
            void SearchResultOnMapMyPinsService::HandlePinAdded(MyPins::SdkModel::MyPinModel*& pMyPin)
            {
                Eegeo_ASSERT(pMyPin != NULL);
                MyPins::SdkModel::MyPinModel& myPinModel(*pMyPin);
                
                if(myPinModel.GetSemanticPinType() == MyPins::SdkModel::SearchResultPoi)
                {
                    const std::string& json = myPinModel.GetTypeMetadata();
                    Search::SdkModel::SearchResultModel myPinSearchResultModel = Search::SdkModel::DeserializeFromJson(json);
                    m_searchResultPinnedCallbacks.ExecuteCallbacks(myPinSearchResultModel);
                }
            }
            
            void SearchResultOnMapMyPinsService::HandlePinRemoved(MyPins::SdkModel::MyPinModel*& pMyPin)
            {
                Eegeo_ASSERT(pMyPin != NULL);
                MyPins::SdkModel::MyPinModel& myPinModel(*pMyPin);
                
                if(myPinModel.GetSemanticPinType() == MyPins::SdkModel::SearchResultPoi)
                {
                    const std::string& json = myPinModel.GetTypeMetadata();
                    Search::SdkModel::SearchResultModel myPinSearchResultModel = Search::SdkModel::DeserializeFromJson(json);
                    m_searchResultUnpinnedCallbacks.ExecuteCallbacks(myPinSearchResultModel);
                }
            }
        }
    }
}
