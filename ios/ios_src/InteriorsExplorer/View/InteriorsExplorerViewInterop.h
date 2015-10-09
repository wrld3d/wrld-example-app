// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsExplorerView.h"
#include "InteriorsExplorerViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"

#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerViewInterop : public IInteriorsExplorerView
            {
            public:
                
                InteriorsExplorerViewInterop(InteriorsExplorerView* pView)
                : m_pView(pView)
                {
                }
                
                void OnDismissed();

                void Dismiss();
                void SelectFloor(int floor);
                
                void SetFloorName(const std::string& name);
                void UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex);
                
                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                
                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();
                
                void SetTouchEnabled(bool enabled);
                
            private:
                
                Eegeo::Helpers::CallbackCollection1<int> m_selectedFloorCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                InteriorsExplorerView* m_pView;
            };
        }
    }
}
