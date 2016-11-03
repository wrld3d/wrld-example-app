// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "IMenuSectionViewModel.h"
#include <vector>

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class IDirectionsMenuView
            {
            public:
                virtual ~IDirectionsMenuView() { }
                
                virtual void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection) = 0;
                
                virtual void RemoveSeachKeyboard() = 0;
                
                virtual void SetSearchInProgress(bool inProgress) = 0;
                
                virtual void SetStartEditText(const std::string& searchText, bool isCategory) = 0;
                
                virtual void SetEndEditText(const std::string& searchText, bool isCategory) = 0;
                
                virtual void SetGeoNamesStartSuggestions(const std::vector<Search::SdkModel::SearchResultModel>& results) = 0;
                
                virtual void SetGeoNamesEndSuggestions(const std::vector<Search::SdkModel::SearchResultModel>& results) = 0;
                
                virtual void HighlightListItem(const int index) = 0;
                
                virtual void CollapseAll() = 0;
                
                virtual void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback2<const Eegeo::Space::LatLong&,const Eegeo::Space::LatLong&>& callback) = 0;
                virtual void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback2<const Eegeo::Space::LatLong&,const Eegeo::Space::LatLong&>& callback) = 0;
                
                virtual void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void OnExitDirectionsClicked() = 0;
                
                virtual void InsertExitDirectionsCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveExitDirectionsCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertWayPointSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveWayPointSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                
                virtual void HandleWayPointSelected(int index) = 0;
                
                virtual void InsertStartLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                
                virtual void RemoveStartLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)  = 0;
                
                virtual void HandleStartLocationChanged(const std::string& startLocationQuery) = 0;
                
                virtual void InsertEndLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                
                virtual void RemoveEndLocationChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)  = 0;
                
                virtual void HandleEndLocationChanged(const std::string& startLocationQuery) = 0;
                
            };
        }
    }
}