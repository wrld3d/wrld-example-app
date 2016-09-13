// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerView.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;
using namespace System::Reflection;
using namespace System;

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerView::InteriorsExplorerView()
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.InteriorsExplorerView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mUpdateFloors.SetupMethod(m_uiViewClass, m_uiView, "UpdateFloors");
                mSetFloorName.SetupMethod(m_uiViewClass, m_uiView, "SetFloorName");
                mSetSelectedFloor.SetupMethod(m_uiViewClass, m_uiView, "SetSelectedFloor");
                mSetOnScreenStateToIntermediateValue.SetupMethod(m_uiViewClass, m_uiView, "SetOnScreenStateToIntermediateValue");
                mSetFullyOnScreen.SetupMethod(m_uiViewClass, m_uiView, "SetFullyOnScreen");
                mSetFullyOffScreen.SetupMethod(m_uiViewClass, m_uiView, "SetFullyOffScreen");
                mSetTouchEnabled.SetupMethod(m_uiViewClass, m_uiView, "SetTouchEnabled");
                mSetFloorPanelEnabled.SetupMethod(m_uiViewClass, m_uiView, "SetFloorPanelEnabled");
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mPlaySliderAnim.SetupMethod(m_uiViewClass, m_uiView, "PlaySliderShakeAnim");
				mAddTutorialDialogs.SetupMethod(m_uiViewClass, m_uiView, "AddTutorialDialogs");
				mRemoveTutorialDialogs.SetupMethod(m_uiViewClass, m_uiView, "RemoveTutorialDialogs");
				mGetCanShowChangeFloorTutorialDialog.SetupMethod(m_uiViewClass, m_uiView, "GetCanShowChangeFloorTutorialDialog");
            }

            void InteriorsExplorerView::UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex)
            {
                int floorCount = (int)floorShortNames.size();
                array<System::String^>^ floorNames = gcnew array<System::String^>(floorCount);

                for (int floorIndex = 0; floorIndex < floorCount; ++floorIndex)
                {
                    floorNames[floorIndex] = ConvertUTF8ToManagedString(floorShortNames[floorIndex]);
                }

                mUpdateFloors(floorNames, currentlySelectedFloorIndex);
            }

            void InteriorsExplorerView::SetFloorName(const std::string& name)
            {
                mSetFloorName(ConvertUTF8ToManagedString(name));
            }

            void InteriorsExplorerView::SetFloorSelectionDrag(float dragParam)
            {
                m_floorSelectionDraggedCallbacks.ExecuteCallbacks(dragParam);
            }

            void InteriorsExplorerView::SetOnScreenStateToIntermediateValue(float value)
            {
                mSetOnScreenStateToIntermediateValue(value);
            }

            void InteriorsExplorerView::SetSelectedFloorIndex(int index)
            {
                mSetSelectedFloor(index);
            }

            void InteriorsExplorerView::SetFullyOnScreen()
            {
                mSetFullyOnScreen();
            }

            void InteriorsExplorerView::SetFullyOffScreen()
            {
                mSetFullyOffScreen();
            }

            void InteriorsExplorerView::SetTouchEnabled(bool enabled)
            {
                mSetTouchEnabled(enabled);
            }

            void InteriorsExplorerView::SetFloorPanelEnabled(bool enabled)
            {
                mSetFloorPanelEnabled(enabled);
            }

            void InteriorsExplorerView::Dismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void InteriorsExplorerView::SelectFloor(int floor)
            {
                m_selectedFloorCallbacks.ExecuteCallbacks(floor);
            }

            void InteriorsExplorerView::OnDismissed()
            {
            }

			void InteriorsExplorerView::AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
			{
				mAddTutorialDialogs(showExitDialog, showChangeFloorDialog);
			}

			void InteriorsExplorerView::RemoveTutorialDialogs()
			{
				mRemoveTutorialDialogs();
			}

			bool InteriorsExplorerView::GetCanShowChangeFloorTutorialDialog()
			{
				return (bool) mGetCanShowChangeFloorTutorialDialog.Call<System::Boolean^>();
			}

            void InteriorsExplorerView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::PlaySliderAnim()
            {
                mPlaySliderAnim();
            }

            InteriorsExplorerView::~InteriorsExplorerView()
            {
                mDestroy();
            }
        }
    }
}