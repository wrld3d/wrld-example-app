// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSearchResultPoiViewModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            DesktopSearchResultPoiViewModel::DesktopSearchResultPoiViewModel(Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
                : m_searchResultModel()
                , m_openable(identity, reactionControllerModel)
            {

            }

            DesktopSearchResultPoiViewModel::~DesktopSearchResultPoiViewModel()
            {

            }

            bool DesktopSearchResultPoiViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }

            const Search::SdkModel::SearchResultModel& DesktopSearchResultPoiViewModel::GetSearchResultModel() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_searchResultModel;
            }
            
            bool DesktopSearchResultPoiViewModel::IsPinned() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read IsPinned when view model is not open.\n");
                return m_isPinned;
            }
            
            void DesktopSearchResultPoiViewModel::ToggleIsPinned()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot toggle IsPinned when view model is not open.\n");
                m_isPinned = !m_isPinned;
            }

            bool DesktopSearchResultPoiViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            void DesktopSearchResultPoiViewModel::Open(const Search::SdkModel::SearchResultModel& searchResultModel,
                                                bool isPinned)
            {
                if (m_openable.IsFullyOpen())
                {
                    if (m_searchResultModel.GetIdentifier() == searchResultModel.GetIdentifier())
                    {
                        return;
                    }
                    else if (m_searchResultModel.GetVendor() != searchResultModel.GetVendor())
                    {
                        Close();
                    }
                }
                
                m_openable.Open(false);
                m_searchResultModel = searchResultModel;
                m_isPinned = isPinned;
                m_openedCallbacks.ExecuteCallbacks();
            }

            void DesktopSearchResultPoiViewModel::Close()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");

                {
                    const bool closed = m_openable.Close(false);
                    Eegeo_ASSERT(closed, "Failed to close");
                }

                m_closedCallbacks.ExecuteCallbacks();
            }

            OpenableControl::View::IOpenableControlViewModel& DesktopSearchResultPoiViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void DesktopSearchResultPoiViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void DesktopSearchResultPoiViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void DesktopSearchResultPoiViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void DesktopSearchResultPoiViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
        }
    }
}
