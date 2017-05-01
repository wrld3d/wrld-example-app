// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuView.h"
#include "ICallback.h"
#include "IFunc.h"
#include "CallbackCollection.h"
#include "MenuItemModel.h"
#include "AndroidNativeState.h"

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

                void CallVoidVoidFunction(const char* func);
            protected:
                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                TSections m_currentSections;

            public:
                MenuView(AndroidNativeState& nativeState,
                         const std::string& viewClassName);

                virtual ~MenuView();

                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function);

                void SetCanInteract(bool canInteract);

                void ClearTryDragFunc();

                float GetAnimationProgress() const;

                bool IsAnimating() const;

                bool IsTableAnimating() const { return false; } // TODO: IR

                void UpdateAnimation(float dt);

                void UpdateTableAnimation(float dt) {} // TODO: IR

                void UpdateMenuSectionViews(TSections& sections, bool contentsChanged);

                void SetFullyOnScreenOpen();

                void SetFullyOnScreenClosed();

                void SetTableCanInteract(bool canInteract) {} // TODO: IR

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

                virtual void HandleItemSelected(int sectionIndex, int itemIndex);

                bool CallBeginDrag();

                void ToggleSection(int sectionIndex);
            };
        }
    }
}
