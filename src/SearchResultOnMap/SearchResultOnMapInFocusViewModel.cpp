// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapInFocusViewModel.h"
#include "LatLongAltitude.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapInFocusViewModel::SearchResultOnMapInFocusViewModel(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
		        Eegeo::Helpers::TIdentity identity)
			: m_isOpen(false)
			, m_searchResultModel("", "", Eegeo::Space::LatLong(0.f, 0.f), "", "", "", "", "")
			, m_searchResultPoiViewModel(searchResultPoiViewModel)
			, m_screenControl(identity)
		{

		}

		SearchResultOnMapInFocusViewModel::~SearchResultOnMapInFocusViewModel()
		{

		}

		const Search::SearchResultModel& SearchResultOnMapInFocusViewModel::GetSearchResultModel() const
		{
			Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
			return m_searchResultModel;
		}

		bool SearchResultOnMapInFocusViewModel::IsOpen() const
		{
			return m_isOpen;
		}

		const Eegeo::v2& SearchResultOnMapInFocusViewModel::ScreenLocation() const
		{
			Eegeo_ASSERT(IsOpen(), "Cannot read ScreenLocation when view model is not open.\n");
			return m_screenPos;
		}

		void SearchResultOnMapInFocusViewModel::SelectFocussedResult()
		{
			Eegeo_ASSERT(IsOpen(), "Cannot SelectFocussedResult when view model is not open.\n");
			m_searchResultPoiViewModel.Open(m_searchResultModel);
		}

		void SearchResultOnMapInFocusViewModel::Open(const Search::SearchResultModel& searchResultModel, const Eegeo::v2& screenPos)
		{
			m_searchResultModel = searchResultModel;
			m_isOpen = true;
			m_screenPos = screenPos;
			m_openedCallbacks.ExecuteCallbacks();
		}

		void SearchResultOnMapInFocusViewModel::Close()
		{
			Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");
			m_isOpen = false;
			m_closedCallbacks.ExecuteCallbacks();
		}

		void SearchResultOnMapInFocusViewModel::UpdateScreenLocation(const Eegeo::v2 &screenPos)
		{
			Eegeo_ASSERT(IsOpen(), "Cannot UpdateScreenLocation when view model is not open.\n");
			m_screenPos = screenPos;
			m_updateCallbacks.ExecuteCallbacks();
		}

		ScreenControlViewModel::IScreenControlViewModel& SearchResultOnMapInFocusViewModel::GetScreenControlViewModel()
		{
			return m_screenControl;
		}

		void SearchResultOnMapInFocusViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
		{
			m_openedCallbacks.AddCallback(openedCallback);
		}

		void SearchResultOnMapInFocusViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
		{
			m_openedCallbacks.RemoveCallback(openedCallback);
		}

		void SearchResultOnMapInFocusViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
		{
			m_closedCallbacks.AddCallback(closedCallback);
		}

		void SearchResultOnMapInFocusViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
		{
			m_closedCallbacks.RemoveCallback(closedCallback);
		}

		void SearchResultOnMapInFocusViewModel::InsertUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback)
		{
			m_updateCallbacks.AddCallback(updateCallback);
		}

		void SearchResultOnMapInFocusViewModel::RemoveUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback)
		{
			m_updateCallbacks.RemoveCallback(updateCallback);
		}
	}
}
