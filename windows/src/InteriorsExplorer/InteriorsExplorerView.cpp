// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerView.h"
#include "InteriorsExplorerViewImpl.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerView::InteriorsExplorerView()
            {
                m_pImpl = Eegeo_NEW(InteriorsExplorerViewImpl)();
            }

            InteriorsExplorerView::~InteriorsExplorerView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void InteriorsExplorerView::UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex)
            {
                m_pImpl->UpdateFloors(floorShortNames, currentlySelectedFloorIndex);
            }

            void InteriorsExplorerView::SetFloorName(const std::string& name)
            {
                m_pImpl->SetFloorName(name);
            }

            void InteriorsExplorerView::SetFloorSelectionDrag(float dragParam)
            {
                m_pImpl->SetFloorSelectionDrag(dragParam);
            }

            void InteriorsExplorerView::SetOnScreenStateToIntermediateValue(float value)
            {
                m_pImpl->SetOnScreenStateToIntermediateValue(value);
            }

            void InteriorsExplorerView::SetSelectedFloorIndex(int index)
            {
                m_pImpl->SetSelectedFloorIndex(index);
            }

            void InteriorsExplorerView::SetFullyOnScreen()
            {
                m_pImpl->SetFullyOnScreen();
            }

            void InteriorsExplorerView::SetFullyOffScreen()
            {
                m_pImpl->SetFullyOffScreen();
            }

            void InteriorsExplorerView::SetTouchEnabled(bool enabled)
            {
                m_pImpl->SetTouchEnabled(enabled);
            }

            void InteriorsExplorerView::SetFloorPanelEnabled(bool enabled)
            {
                m_pImpl->SetFloorPanelEnabled(enabled);
            }

            void InteriorsExplorerView::Dismiss()
            {
                m_pImpl->Dismiss();
            }

            void InteriorsExplorerView::SelectFloor(int floor)
            {
                m_pImpl->SelectFloor(floor);
            }

            void InteriorsExplorerView::OnDismissed()
            {
                m_pImpl->OnDismissed();
            }

			void InteriorsExplorerView::AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
			{
                m_pImpl->AddTutorialDialogs(showExitDialog, showChangeFloorDialog);
			}

			void InteriorsExplorerView::RemoveTutorialDialogs()
			{
                m_pImpl->RemoveTutorialDialogs();
			}

			bool InteriorsExplorerView::GetCanShowChangeFloorTutorialDialog()
			{
				return m_pImpl->GetCanShowChangeFloorTutorialDialog();
			}

            void InteriorsExplorerView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertDismissedCallback(callback);
            }

            void InteriorsExplorerView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveDismissedCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_pImpl->InsertFloorSelectedCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_pImpl->RemoveFloorSelectedCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->InsertFloorSelectionDraggedCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_pImpl->RemoveFloorSelectionDraggedCallback(callback);
            }

            void InteriorsExplorerView::PlaySliderAnim()
            {
                m_pImpl->PlaySliderAnim();
            }
        }
    }
}