// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            class IInteriorsView : public ScreenControl::View::IScreenControlView
            {
            public:
                
                virtual ~IInteriorsView() { }
                
                virtual void Show() = 0;
                virtual void Dismiss() = 0;
                virtual void SelectFloor(int floor) = 0;
                
                virtual void OnDismissed() = 0;
                virtual void SetFloorCount(int floorCount) = 0;
                virtual void SetFloorName(const std::string& name) = 0;
                
                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
            };
        }
    }
}
