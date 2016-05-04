// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"
#include "SearchServiceBase.h"
#include "ICallback.h"
#include "CategorySearchModel.h"
#include "Interiors.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                class CombinedSearchService
                : public Search::SdkModel::SearchServiceBase
                {
                public:
                    
                    CombinedSearchService(const std::map<std::string, Search::SdkModel::ISearchService*>& searchServices,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);
                    
                    ~CombinedSearchService();
                    
                    bool CanHandleCategory(const std::string& category) const;
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    
                    void OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results, const bool& success);
                    void ShowFailureDialog();
                    void HandleAlertDismissed();
                    
                private:
                    
                    std::map<std::string,Search::SdkModel::ISearchService*> m_searchServices;
                    
                    Eegeo::Helpers::TCallback3<CombinedSearchService,
                                               const Search::SdkModel::SearchQuery&,
                                               const std::vector<Search::SdkModel::SearchResultModel>&,
                                               const bool&> m_searchQueryResponseCallback;
                    
                    int m_pendingResultsLeft;
                    std::vector<Search::SdkModel::SearchResultModel> m_combinedResults;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<CombinedSearchService> m_alertBoxHandler;
                    bool m_showAlertBoxNextFailure;
                    bool m_hasActiveQuery;
                    bool m_anyRequestsFailed;
                    
                };
            }
        }
    }
}
