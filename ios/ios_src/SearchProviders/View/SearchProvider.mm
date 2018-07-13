// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchProvider.h"
#include "WidgetSearchResultModel.h"
#include "WidgetQueryContext.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
        SearchProvider::SearchProvider()
        : m_pCurrentRequest(nullptr)
        , m_pCurrentSuggestion(nullptr)
        {
        }

        SearchProvider::~SearchProvider()
        {
        }

        void SearchProvider::InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_autocompleteSuggestionsCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_autocompleteSuggestionsCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.RemoveCallback(callback);
        }
        
        void SearchProvider::InsertSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_suggestionsCancelledCallbacks.AddCallback(callback);
        }
        
        void SearchProvider::RemoveSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_suggestionsCancelledCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::OnSearchResponseReceived(const bool success, const TSearchResults& searchResults)
        {
            UpdateResults(success, searchResults, m_pCurrentRequest);
        }

        void SearchProvider::OnAutocompleteSuggestionsResponseReceived(const bool success, const TSearchResults& searchResults)
        {
            UpdateResults(success, searchResults, m_pCurrentSuggestion);
        }
        
        void SearchProvider::CancelAutocompleteRequest()
        {
            m_suggestionsCancelledCallbacks.ExecuteCallbacks();
        }

        void SearchProvider::UpdateResults(const bool success, const TSearchResults& searchResults, WRLDSearchRequest* searchRequest)
        {
            typedef NSMutableArray< id<WRLDSearchResultModel> > WRLDMutableSearchResultsCollection;
            
            WRLDMutableSearchResultsCollection* widgetSearchResults = [[WRLDMutableSearchResultsCollection alloc] init];
            
            if(!success)
            {
                WRLDMutableSearchResultsCollection* widgetSearchResults = [[WRLDMutableSearchResultsCollection alloc] init];
                [searchRequest didComplete: NO withResults: widgetSearchResults];
                return;
            }
            
            for(int i = 0; i < searchResults.size(); i++)
            {
                WidgetSearchResultModel* widgetSearchResult = [[WidgetSearchResultModel alloc] init];
                
                widgetSearchResult.title = [NSString stringWithUTF8String:searchResults.at(i).GetName().c_str()];
                widgetSearchResult.subTitle = [NSString stringWithUTF8String:searchResults.at(i).GetDescription().c_str()];
                widgetSearchResult.iconKey = [NSString stringWithUTF8String:searchResults.at(i).GetIconName().c_str()];
                widgetSearchResult.index = (NSInteger) i;
                
                [widgetSearchResults addObject: widgetSearchResult];
            }
            
            [searchRequest didComplete:YES withResults:widgetSearchResults];
        }

        void SearchProvider::PerformSearch(WRLDSearchRequest* searchRequest)
        {
            m_pCurrentRequest = searchRequest;
            std::string searchQuery = [m_pCurrentRequest.queryString cStringUsingEncoding: NSUTF8StringEncoding];
            
            WidgetQueryContext* widgetQueryContext = (WidgetQueryContext*) m_pCurrentRequest.queryContext;
            
            if (widgetQueryContext)
            {
                std::string tagText = [widgetQueryContext.tagText cStringUsingEncoding: NSUTF8StringEncoding];
                const Eegeo::Space::LatLongAltitude& location = Eegeo::Space::LatLongAltitude(widgetQueryContext.latitude,
                                                                                              widgetQueryContext.longtitude,
                                                                                              widgetQueryContext.altitude);

                const SearchMenu::View::QueryContext& queryContext =
                    (widgetQueryContext.usesLocation ?
                        SearchMenu::View::QueryContext(widgetQueryContext.clearPreviousResults,
                                                       widgetQueryContext.isTag,
                                                       tagText,
                                                       widgetQueryContext.shouldTryInterior,
                                                       location,
                                                       widgetQueryContext.radius) :
                     widgetQueryContext.usesRadius ?
                        SearchMenu::View::QueryContext(widgetQueryContext.clearPreviousResults,
                                                       widgetQueryContext.isTag,
                                                       tagText,
                                                       widgetQueryContext.shouldTryInterior,
                                                       widgetQueryContext.radius) :
                        SearchMenu::View::QueryContext(widgetQueryContext.clearPreviousResults,
                                                       widgetQueryContext.isTag,
                                                       tagText,
                                                       widgetQueryContext.shouldTryInterior));

                m_searchWithContextCallbacks.ExecuteCallbacks(searchQuery, queryContext);
            }
            else
            {
                m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
            }
        }

        void SearchProvider::PerformAutocompleteSuggestions(WRLDSearchRequest* searchRequest)
        {
            m_pCurrentSuggestion = searchRequest;
            std::string searchQuery = [m_pCurrentSuggestion.queryString cStringUsingEncoding: NSUTF8StringEncoding];
            m_autocompleteSuggestionsCallbacks.ExecuteCallbacks(searchQuery);
        }
    }
}
