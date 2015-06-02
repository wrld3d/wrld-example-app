// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsView.h"
#include "IosInteriorViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            class IosInteriorViewInterop : public IInteriorsView
            {
            public:
                
                IosInteriorViewInterop(IosInteriorView* pView)
                : m_pView(pView)
                {
                }
                
                void OnDismissed();
                void Show();

                void Dismiss();
                void SelectFloor(int floor);
                
                void SetFloorCount(int floorCount);
                void SetFloorName(const std::string& name);
                
                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                
                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();
                
            private:
                
                Eegeo::Helpers::CallbackCollection1<int> m_selectedFloorCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                IosInteriorView* m_pView;
            };
        }
    }
}
