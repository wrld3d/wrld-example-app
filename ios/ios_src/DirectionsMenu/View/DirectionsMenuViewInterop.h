// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "CallbackCollection.h"
#include "IDirectionsMenuView.h"
#include "IMenuSectionViewModel.h"
#include "DirectionsMenuView.h"
#include "SearchResultViewClearedMessage.h"
#include "Types.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class DirectionsMenuViewInterop : private Eegeo::NonCopyable, public IDirectionsMenuView
            {
            private:
                DirectionsMenuView* m_pView;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_wayPointSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_exitDirectionsCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_startLocationCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_endLocationCallbacks;
                
            public:
                
                DirectionsMenuViewInterop(DirectionsMenuView* pView)
                    : m_pView(pView)
                {
                }
                
                virtual void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
                {
                    [m_pView SetSearchSection:&searchSection];
                }
                
                void RemoveSeachKeyboard()
                {
                }

                void SetSearchInProgress(bool inProgress)
                {
                }
                
                void SetStartEditText(const std::string& searchText, bool isCategory)
                {
                
                }
                
                void SetEndEditText(const std::string& searchText, bool isCategory)
                {
                
                }
                
                void SearchPerformed(const std::string& searchQuery)
                {
                    m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
                }
                
                void CollapseAll()
                {
                    [m_pView CollapseAll];
                }
                
                void HighlightListItem(const int index)
                {
                    [m_pView HighlightItemIndex:index];
                }
                
                void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_searchPerformedCallbacks.AddCallback(callback);
                }

                void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_searchPerformedCallbacks.RemoveCallback(callback);
                }

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_searchClearedCallbacks.AddCallback(callback);
                }
                
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_searchClearedCallbacks.RemoveCallback(callback);
                }
                
                void OnSearchCleared()
                {
                    m_searchClearedCallbacks.ExecuteCallbacks();
                }
                
                void OnExitDirectionsClicked()
                {
                    m_exitDirectionsCallbacks.ExecuteCallbacks();
                }
                
                void InsertWayPointSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
                {
                    m_wayPointSelectedCallbacks.AddCallback(callback);
                }
                
                void RemoveWayPointSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
                {
                    m_wayPointSelectedCallbacks.RemoveCallback(callback);
                }
                
                void InsertExitDirectionsCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_exitDirectionsCallbacks.AddCallback(callback);
                }
                
                void RemoveExitDirectionsCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_exitDirectionsCallbacks.RemoveCallback(callback);
                }
                
                void HandleWayPointSelected(int index)
                {
                    m_wayPointSelectedCallbacks.ExecuteCallbacks(index);
                }
                
                void InsertStartLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_startLocationCallbacks.AddCallback(callback);
                }
                
                void RemoveStartLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_startLocationCallbacks.RemoveCallback(callback);
                }
                
                void HandleStartLocationChanged(const std::string& startLocationQuery)
                {
                    m_startLocationCallbacks.ExecuteCallbacks(startLocationQuery);
                }
                
                void InsertEndLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_endLocationCallbacks.AddCallback(callback);
                }
                
                void RemoveEndLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_endLocationCallbacks.RemoveCallback(callback);
                }
                
                void HandleEndLocationChanged(const std::string& startLocationQuery)
                {
                    m_endLocationCallbacks.ExecuteCallbacks(startLocationQuery);
                }
                
                
            };
        }
    }
}
