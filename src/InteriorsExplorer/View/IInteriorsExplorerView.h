// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include <string>
#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class IInteriorsExplorerView : public ScreenControl::View::IScreenControlView
            {
            public:
                
                virtual ~IInteriorsExplorerView() { }
                
                virtual void Dismiss() = 0;
                virtual void SelectFloor(int floor) = 0;
                
                virtual void OnDismissed() = 0;
                virtual void SetFloorName(const std::string& name) = 0;
                virtual void UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex) = 0;
                
                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                
                virtual void SetTouchEnabled(bool enabled) = 0;
            };
        }
    }
}
