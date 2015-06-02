//
//  IosInteriorViewInterop.cpp
//  ExampleApp
//
//  Created by eeGeo QA on 29/05/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#include "IosInteriorViewInterop.h"
#include "IosInteriorView.h"
#include <string>

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            void IosInteriorViewInterop::Show()
            {
            }
            
            void IosInteriorViewInterop::Dismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }
            
            void IosInteriorViewInterop::SelectFloor(int floor)
            {
                m_selectedFloorCallbacks.ExecuteCallbacks(floor);
            }
            
            void IosInteriorViewInterop::OnDismissed()
            {
            }
            
            void IosInteriorViewInterop::SetFloorCount(int count)
            {
                [m_pView setFloorCount:count];
            }
            
            void IosInteriorViewInterop::SetFloorName(const std::string& name)
            {
                [m_pView setFloorName:&name];
            }
            
            void IosInteriorViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }
            
            void IosInteriorViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }
            
            void IosInteriorViewInterop::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.AddCallback(callback);
            }
            
            void IosInteriorViewInterop::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.RemoveCallback(callback);
            }
            
            void IosInteriorViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue: value];
            }
            
            void IosInteriorViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }
            
            void IosInteriorViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }
        }
    }
}