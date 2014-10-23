// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapViewController.h"
#include "Types.h"
#include "SearchResultOnMapView.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

@class SearchResultOnMapViewController;

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapViewControllerInterop : private Eegeo::NonCopyable
        {
            SearchResultOnMapViewController* m_pInstance;
            ISearchResultOnMapInFocusViewModel& m_searchResultOnMapInFocusViewModel;
            ScreenControlViewModel::IScreenControlViewModel& m_searchResultPoiScreenControlViewModel;
            
            Eegeo::Helpers::ICallback0* m_pSearchResultOnMapFocusOpenedCallback;
            Eegeo::Helpers::ICallback0* m_pSearchResultOnMapFocusClosedCallback;
            Eegeo::Helpers::ICallback0* m_pSearchResultOnMapFocusUpdatedCallback;
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;
            
            void SearchResultOnMapFocusOpenedCallback()
            {
                [m_pInstance open];
            }
            
            void SearchResultOnMapFocusClosedCallback()
            {
                [m_pInstance close];
            }
            
            void SearchResultOnMapFocusUpdatedCallback()
            {
                [m_pInstance updateScreenLocation];
            }
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pInstance handleScreenStateChanged:m_searchResultPoiScreenControlViewModel.OnScreenState()];
            }
            
        public:
            SearchResultOnMapViewControllerInterop(SearchResultOnMapViewController* pInstance,
                                                   ExampleApp::SearchResultOnMap::ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
                                                   ScreenControlViewModel::IScreenControlViewModel& searchResultPoiScreenControlViewModel)
            : m_pInstance(pInstance)
            , m_searchResultOnMapInFocusViewModel(searchResultOnMapInFocusViewModel)
            , m_searchResultPoiScreenControlViewModel(searchResultPoiScreenControlViewModel)
            , m_pSearchResultOnMapFocusOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewControllerInterop>)(this, &SearchResultOnMapViewControllerInterop::SearchResultOnMapFocusOpenedCallback))
            , m_pSearchResultOnMapFocusClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewControllerInterop>)(this, &SearchResultOnMapViewControllerInterop::SearchResultOnMapFocusClosedCallback))
            , m_pSearchResultOnMapFocusUpdatedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewControllerInterop>)(this, &SearchResultOnMapViewControllerInterop::SearchResultOnMapFocusUpdatedCallback))
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchResultOnMapViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &SearchResultOnMapViewControllerInterop::OnScreenStateChangedCallback))
            {
                m_searchResultOnMapInFocusViewModel.InsertOpenedCallback(*m_pSearchResultOnMapFocusOpenedCallback);
                m_searchResultOnMapInFocusViewModel.InsertClosedCallback(*m_pSearchResultOnMapFocusClosedCallback);
                m_searchResultOnMapInFocusViewModel.InsertUpdateCallback(*m_pSearchResultOnMapFocusUpdatedCallback);
                
                m_searchResultPoiScreenControlViewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~SearchResultOnMapViewControllerInterop()
            {
                m_searchResultPoiScreenControlViewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
                
                m_searchResultOnMapInFocusViewModel.RemoveUpdateCallback(*m_pSearchResultOnMapFocusUpdatedCallback);
                m_searchResultOnMapInFocusViewModel.RemoveOpenedCallback(*m_pSearchResultOnMapFocusOpenedCallback);
                m_searchResultOnMapInFocusViewModel.RemoveClosedCallback(*m_pSearchResultOnMapFocusClosedCallback);
                
                Eegeo_DELETE m_pSearchResultOnMapFocusUpdatedCallback;
                Eegeo_DELETE m_pSearchResultOnMapFocusOpenedCallback;
                Eegeo_DELETE m_pSearchResultOnMapFocusClosedCallback;
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
            }
        };
    }
}
