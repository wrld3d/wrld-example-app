// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewInterop.h"
#include "InteriorsExplorerView.h"
#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            void InteriorsExplorerViewInterop::Dismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }
            
            void InteriorsExplorerViewInterop::SelectFloor(int floor)
            {
                m_selectedFloorCallbacks.ExecuteCallbacks(floor);
            }
            
            void InteriorsExplorerViewInterop::SetFloorSelectionDrag(float floorButtonParameter)
            {
                m_floorSelectionDraggedCallbacks.ExecuteCallbacks(floorButtonParameter);
            }
            
            void InteriorsExplorerViewInterop::OnDismissed()
            {
            }
            
            void InteriorsExplorerViewInterop::UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex)
            {
                [m_pView updateFloors: floorShortNames
                     withCurrentFloor: currentlySelectedFloorIndex];
            }
            
            void InteriorsExplorerViewInterop::SetFloorName(const std::string& name)
            {
                [m_pView setFloorName:&name];
            }
            
            void InteriorsExplorerViewInterop::SetSelectedFloorIndex(int index)
            {
                [m_pView setSelectedFloor:index];
            }
            
            void InteriorsExplorerViewInterop::AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
            {
                [m_pTutorialView show: showExitDialog : showChangeFloorDialog];
            }
            
            void InteriorsExplorerViewInterop::RemoveTutorialDialogs()
            {
                [m_pTutorialView hide];
            }
            
            bool InteriorsExplorerViewInterop::GetCanShowChangeFloorTutorialDialog()
            {
                return [m_pView GetCanShowChangeFloorTutorialDialog];
            }
            
            void InteriorsExplorerViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerViewInterop::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pView setOnScreenStateToIntermediateValue: value];
            }
            
            void InteriorsExplorerViewInterop::SetFullyOnScreen()
            {
                [m_pView setFullyOnScreen];
            }
            
            void InteriorsExplorerViewInterop::SetFullyOffScreen()
            {
                [m_pView setFullyOffScreen];
            }
            
            void InteriorsExplorerViewInterop::SetTouchEnabled(bool enabled)
            {
                [m_pView setTouchEnabled: enabled];
            }
            
            void InteriorsExplorerViewInterop::PlaySliderAnim()
            {
                [m_pView playSliderShakeAnim];
            }
        }
    }
}