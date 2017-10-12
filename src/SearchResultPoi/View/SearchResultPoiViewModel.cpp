// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModel.h"
#include "LatLongAltitude.h"
#include "SwallowSearchConstants.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewModel::SearchResultPoiViewModel(Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
                : m_searchResultModel()
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

            const Search::SdkModel::SearchResultModel& SearchResultPoiViewModel::GetSearchResultModel() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_searchResultModel;
            }
            
            bool SearchResultPoiViewModel::IsPinned() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read IsPinned when view model is not open.\n");
                return m_isPinned;
            }
            
            void SearchResultPoiViewModel::ToggleIsPinned()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot toggle IsPinned when view model is not open.\n");
                m_isPinned = !m_isPinned;
            }

            bool SearchResultPoiViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            void SearchResultPoiViewModel::Open(const Search::SdkModel::SearchResultModel& searchResultModel,
                                                bool isPinned)
            {
                const std::string& vendor = searchResultModel.GetVendor();
                const std::string& primaryTag = searchResultModel.GetPrimaryTag();
                
                bool canOpenPOIView = false;
                if(vendor == ExampleApp::Search::YelpVendorName
                   || vendor == ExampleApp::Search::GeoNamesVendorName)
                {
                    canOpenPOIView = true;
                }
                else if(vendor == ExampleApp::Search::EegeoVendorName)
                {
                    if(primaryTag == ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::TRAINING_ROOM_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME
                       || primaryTag == ExampleApp::Search::Swallow::SearchConstants::SHOW_POI_CARD_NAME)
                    {
                        canOpenPOIView = true;
                    }
                }
                
                if(canOpenPOIView)
                {
                    Eegeo_ASSERT(!IsOpen(), "Cannot open SearchResultPoiViewModel when already open.\n");
                    if(m_openable.Open())
                    {
                        m_searchResultModel = searchResultModel;
                        m_isPinned = isPinned;
                        m_openedCallbacks.ExecuteCallbacks();
                    }
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

            OpenableControl::View::IOpenableControlViewModel& SearchResultPoiViewModel::GetOpenableControl()
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
}
