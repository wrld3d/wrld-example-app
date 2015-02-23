// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultOnMapMyPinsService.h"
#include "Types.h"
#include "MyPins.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class SearchResultOnMapMyPinsService : public ISearchResultOnMapMyPinsService, private Eegeo::NonCopyable
            {
                MyPins::SdkModel::IMyPinsRepository& m_myPinsRepository;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_searchResultPinnedCallbacks;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_searchResultUnpinnedCallbacks;
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapMyPinsService, MyPins::SdkModel::MyPinModel*> m_pinAddedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapMyPinsService, MyPins::SdkModel::MyPinModel*> m_pinRemovedCallback;
                
                void HandlePinAdded(MyPins::SdkModel::MyPinModel*& pMyPin);
                void HandlePinRemoved(MyPins::SdkModel::MyPinModel*& pMyPin);
                
            public:
                SearchResultOnMapMyPinsService(MyPins::SdkModel::IMyPinsRepository& myPinsRepository);
                
                ~SearchResultOnMapMyPinsService();
                
                bool IsSearchResultPinned(const Search::SdkModel::SearchResultModel& searchResult) const;
                
                void InsertSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void InsertSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
            };
        }
    }
}
