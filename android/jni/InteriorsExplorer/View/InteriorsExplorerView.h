// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsExplorerView.h"
#include "InteriorsExplorerViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "AndroidNativeState.h"

#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerView : public IInteriorsExplorerView
            {
            public:

                InteriorsExplorerView(AndroidNativeState& nativeState);
                ~InteriorsExplorerView();

                void OnDismissed();

                void Dismiss();
                void SelectFloor(int floor);
                void SetFloorSelectionDrag(float dragParam);

                void SetFloorName(const std::string& name);
                void SetSelectedFloorIndex(int index);
                void UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex);

                void AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog);
                void RemoveTutorialDialogs();
                bool GetCanShowChangeFloorTutorialDialog();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);
                void RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

                void SetTouchEnabled(bool enabled);

                void PlaySliderAnim();

            private:
                jclass m_uiViewClass;
                jobject m_uiView;
                jobject m_uiTutorialView;

                Eegeo::Helpers::CallbackCollection1<int> m_selectedFloorCallbacks;
                Eegeo::Helpers::CallbackCollection1<float> m_floorSelectionDraggedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                AndroidNativeState& m_nativeState;
            };
        }
    }
}
