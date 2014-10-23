// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewController.h"
#include "Types.h"
#include "SearchResultPoiView.h"
#include "ISearchResultPoiViewModel.h"
#include "ICallback.h"

@class SearchResultPoiViewController;

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        class SearchResultPoiViewControllerInterop : private Eegeo::NonCopyable
        {
            SearchResultPoiViewController* m_pInstance;
            SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
            
            Eegeo::Helpers::ICallback0* m_pSearchResultPoiOpenedCallback;
            Eegeo::Helpers::ICallback0* m_pSearchResultPoiClosedCallback;
            
            void SearchResultPoiOpenedCallback()
            {
                [m_pInstance openWithModel:m_searchResultPoiViewModel.GetSearchResultModel()];
            }
            
            void SearchResultPoiClosedCallback()
            {
                [m_pInstance close];
            }
            
        public:
            SearchResultPoiViewControllerInterop(SearchResultPoiViewController* pInstance,
                                                 ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_pInstance(pInstance)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_pSearchResultPoiOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultPoiViewControllerInterop>)(this, &SearchResultPoiViewControllerInterop::SearchResultPoiOpenedCallback))
            , m_pSearchResultPoiClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultPoiViewControllerInterop>)(this, &SearchResultPoiViewControllerInterop::SearchResultPoiClosedCallback))
            {
                m_searchResultPoiViewModel.InsertOpenedCallback(*m_pSearchResultPoiOpenedCallback);
                m_searchResultPoiViewModel.InsertClosedCallback(*m_pSearchResultPoiClosedCallback);
            }
            
            ~SearchResultPoiViewControllerInterop()
            {
                
                m_searchResultPoiViewModel.RemoveOpenedCallback(*m_pSearchResultPoiOpenedCallback);
                m_searchResultPoiViewModel.RemoveClosedCallback(*m_pSearchResultPoiClosedCallback);
                
                Eegeo_DELETE m_pSearchResultPoiOpenedCallback;
                Eegeo_DELETE m_pSearchResultPoiClosedCallback;
            }
        };
    }
}
