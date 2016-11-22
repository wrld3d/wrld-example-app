// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewImpl.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;
using namespace System::Reflection;
using namespace System;

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewImpl::InteriorsExplorerViewImpl()
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

            InteriorsExplorerViewImpl::~InteriorsExplorerViewImpl()
            {
                mDestroy();
            }

            void InteriorsExplorerViewImpl::UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex)
            {
                int floorCount = (int)floorShortNames.size();
                array<System::String^>^ floorNames = gcnew array<System::String^>(floorCount);

                for (int floorIndex = 0; floorIndex < floorCount; ++floorIndex)
                {
                    floorNames[floorIndex] = ConvertUTF8ToManagedString(floorShortNames[floorIndex]);
                }

                mUpdateFloors(floorNames, currentlySelectedFloorIndex);
            }

            void InteriorsExplorerViewImpl::SetFloorName(const std::string& name)
            {
                mSetFloorName(ConvertUTF8ToManagedString(name));
            }

            void InteriorsExplorerViewImpl::SetFloorSelectionDrag(float dragParam)
            {
                m_floorSelectionDraggedCallbacks.ExecuteCallbacks(dragParam);
            }

            void InteriorsExplorerViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                mSetOnScreenStateToIntermediateValue(value);
            }

            void InteriorsExplorerViewImpl::SetSelectedFloorIndex(int index)
            {
                mSetSelectedFloor(index);
            }

            void InteriorsExplorerViewImpl::SetFullyOnScreen()
            {
                mSetFullyOnScreen();
            }

            void InteriorsExplorerViewImpl::SetFullyOffScreen()
            {
                mSetFullyOffScreen();
            }

            void InteriorsExplorerViewImpl::SetTouchEnabled(bool enabled)
            {
                mSetTouchEnabled(enabled);
            }

            void InteriorsExplorerViewImpl::SetFloorPanelEnabled(bool enabled)
            {
                mSetFloorPanelEnabled(enabled);
            }

            void InteriorsExplorerViewImpl::Dismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void InteriorsExplorerViewImpl::SelectFloor(int floor)
            {
                m_selectedFloorCallbacks.ExecuteCallbacks(floor);
            }

            void InteriorsExplorerViewImpl::OnDismissed()
            {
            }

			void InteriorsExplorerViewImpl::AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
			{
				mAddTutorialDialogs(showExitDialog, showChangeFloorDialog);
			}

			void InteriorsExplorerViewImpl::RemoveTutorialDialogs()
			{
				mRemoveTutorialDialogs();
			}

			bool InteriorsExplorerViewImpl::GetCanShowChangeFloorTutorialDialog()
			{
				return (bool) mGetCanShowChangeFloorTutorialDialog.Call<System::Boolean^>();
			}

            void InteriorsExplorerViewImpl::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerViewImpl::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerViewImpl::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerViewImpl::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_selectedFloorCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerViewImpl::InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerViewImpl::RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_floorSelectionDraggedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerViewImpl::PlaySliderAnim()
            {
                mPlaySliderAnim();
            }
        }
    }
}