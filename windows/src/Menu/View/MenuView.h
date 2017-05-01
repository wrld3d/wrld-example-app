// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuView.h"
#include "ICallback.h"
#include "IFunc.h"
#include "CallbackCollection.h"
#include "MenuItemModel.h"
#include "WindowsNativeState.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuView : public IMenuView, private Eegeo::NonCopyable
            {
            private:
                Eegeo::Helpers::IFunc0<bool>* m_pTryDragFunc;
                Eegeo::Helpers::CallbackCollection0 m_onViewClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenStartedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onDragStartedCallbacks;
                Eegeo::Helpers::CallbackCollection1<float> m_onDragCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onDragCompletedCallbacks;
                Eegeo::Helpers::CallbackCollection2<int, int> m_onItemSelectedCallbacks;

                Helpers::ReflectionHelpers::Method<void> Destroy;
                Helpers::ReflectionHelpers::Method<void> NormalisedAnimationProgress;
                Helpers::ReflectionHelpers::Method<void> IsAnimatingCSharp;
                Helpers::ReflectionHelpers::Method<float> UpdateAnimationCSharp;
                Helpers::ReflectionHelpers::Method<System::IntPtr, array<System::String^>^, array<System::Int32>^,
                                        array<System::Boolean>^, array<System::String^>^> PopulateData;
                Helpers::ReflectionHelpers::Method<void> AnimateToOpenOnScreen;
                Helpers::ReflectionHelpers::Method<void> AnimateToClosedOnScreen;
                Helpers::ReflectionHelpers::Method<void> AnimateOffScreen;
                Helpers::ReflectionHelpers::Method<float> AnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<int> mToggleSection;

            protected:
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

            public:
                MenuView(WindowsNativeState& nativeState,
                         const std::string& viewClassName,
                         bool isInKioskMode);

                virtual ~MenuView();

                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function);

                void SetCanInteract(bool canInteract);

                void ClearTryDragFunc();

                float GetAnimationProgress() const;

                bool IsAnimating() const;

                void UpdateAnimation(float dt);

                void UpdateMenuSectionViews(TSections& sections, bool contentsChanged);

                void SetFullyOnScreenOpen();

                void SetFullyOnScreenClosed();

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback);

                void InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback);

                void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback);

                void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback);

                void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback);

                void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);

                void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);

                void HandleViewClicked();

                void HandleViewOpenCompleted();

                void HandleViewOpenStarted();

                void HandleViewCloseCompleted();

                void HandleDraggingViewStarted();

                void HandleDraggingViewInProgress(float progress);

                void HandleDraggingViewCompleted();

                void HandleItemSelected(int sectionIndex, int itemIndex);

                bool CallBeginDrag();

                void ToggleSection(int sectionIndex);
            };
        }
    }
}
