// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorsExplorerView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "ReflectionHelpers.h"
#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerView : public IInteriorsExplorerView, private Eegeo::NonCopyable
            {
            private:
                
                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Eegeo::Helpers::CallbackCollection1<int> m_selectedFloorCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                Eegeo::Helpers::CallbackCollection1<float> m_floorSelectionDraggedCallbacks;

                Helpers::ReflectionHelpers::Method<array<System::String^>^, int> mUpdateFloors;
                Helpers::ReflectionHelpers::Method<System::String^> mSetFloorName;
                Helpers::ReflectionHelpers::Method<int> mSetSelectedFloor;
                Helpers::ReflectionHelpers::Method<float> mSetOnScreenStateToIntermediateValue;
                Helpers::ReflectionHelpers::Method<void> mSetFullyOnScreen;
                Helpers::ReflectionHelpers::Method<void> mSetFullyOffScreen;
                Helpers::ReflectionHelpers::Method<bool> mSetTouchEnabled;
                Helpers::ReflectionHelpers::Method<bool> mSetFloorPanelEnabled;
                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mPlaySliderAnim;
				Helpers::ReflectionHelpers::Method<bool,bool> mAddTutorialDialogs;
				Helpers::ReflectionHelpers::Method<void> mRemoveTutorialDialogs;
				Helpers::ReflectionHelpers::Method<void> mGetCanShowChangeFloorTutorialDialog;

            public:
                InteriorsExplorerView();

                ~InteriorsExplorerView();

                void UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex);

                void SetFloorName(const std::string& name);

                void SetFloorSelectionDrag(float dragParam);

                void SetSelectedFloorIndex(int index);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void SetTouchEnabled(bool enabled);

                void SetFloorPanelEnabled(bool enabled);

                void Dismiss();

                void SelectFloor(int floor);

                void OnDismissed();

				void AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog);

				void RemoveTutorialDialogs();

				bool GetCanShowChangeFloorTutorialDialog();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

                void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

                void InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);
                
                void RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);

                void PlaySliderAnim();
            };
        }
    }
}