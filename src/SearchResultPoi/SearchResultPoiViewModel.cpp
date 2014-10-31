// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiViewModel::SearchResultPoiViewModel(Eegeo::Helpers::TIdentity identity,
                                                           Reaction::IReactionControllerModel& reactionControllerModel)
        : m_searchResultModel("", "", Eegeo::Space::LatLong(0.f, 0.f), "", "", "", "", "")
        , m_openable(identity, reactionControllerModel)
        {
            
        }
        
        SearchResultPoiViewModel::~SearchResultPoiViewModel()
        {
            
        }
        
        bool SearchResultPoiViewModel::TryAcquireReactorControl()
        {
            return m_openable.TryAcquireReactorControl();
        }

        const Search::SearchResultModel& SearchResultPoiViewModel::GetSearchResultModel() const
        {
            Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
            return m_searchResultModel;
        }
        
        bool SearchResultPoiViewModel::IsOpen() const
        {
            return m_openable.IsFullyOpen();
        }
        
        void SearchResultPoiViewModel::Open(Search::SearchResultModel& searchResultModel)
        {
            Eegeo_ASSERT(!IsOpen(), "Cannot open SearchResultPoiViewModel when already open.\n");
            if(m_openable.Open())
            {
                m_searchResultModel = searchResultModel;
                m_openedCallbacks.ExecuteCallbacks();
            }
        }
        
        void SearchResultPoiViewModel::Close()
        {
            Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");

            {
            	const bool closed = m_openable.Close();
            	Eegeo_ASSERT(closed, "Failed to close");
            }

            m_closedCallbacks.ExecuteCallbacks();
        }
        
        OpenableControlViewModel::IOpenableControlViewModel& SearchResultPoiViewModel::GetOpenableControl()
        {
            return m_openable;
        }
        
        void SearchResultPoiViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.AddCallback(openedCallback);
        }
        
        void SearchResultPoiViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.RemoveCallback(openedCallback);
        }
        
        void SearchResultPoiViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.AddCallback(closedCallback);
        }
        
        void SearchResultPoiViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.RemoveCallback(closedCallback);
        }
    }
}
