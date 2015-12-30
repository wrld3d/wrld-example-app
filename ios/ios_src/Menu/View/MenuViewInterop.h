// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
#include "MenuViewIncludes.h"
#include "IFunc.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "CustomTableDataProvider.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuViewInterop : public IMenuView
            {
            private:
                MenuView* m_pView;
                CustomTableDataProvider* m_pProvider;
                Eegeo::Helpers::IFunc0<bool>* m_pTryDragFunc;
                Eegeo::Helpers::CallbackCollection0 m_onViewClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onDragStartedCallbacks;
                Eegeo::Helpers::CallbackCollection1<float> m_onDragCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onDragCompletedCallbacks;
                Eegeo::Helpers::CallbackCollection2<int, int> m_onItemSelectedCallbacks;

            public:
                MenuViewInterop(MenuView* pView,
                                CustomTableDataProvider* pProvider)
                    : m_pView(pView)
                    , m_pTryDragFunc(NULL)
                    , m_pProvider(pProvider)
                {
                }

                void SetTableCanInteract(bool canInteract)
                {
                    [m_pView setTableCanInteract:canInteract];
                }

                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
                {
                    Eegeo_ASSERT(m_pTryDragFunc == NULL, "TryDragFunc already set");
                    m_pTryDragFunc = &function;
                }

                void ClearTryDragFunc()
                {
                    m_pTryDragFunc = NULL;
                }

                float GetAnimationProgress() const
                {
                    return [m_pView openOnScreenState];
                }

                bool IsAnimating() const
                {
                    return [m_pView isAnimating];
                }

                void UpdateAnimation(float dt)
                {
                    [m_pView updateAnimation:dt];
                }
                
                void UpdateMenuSectionViews(TSections& sections)
                {
                    [m_pProvider updateMenuSections:&sections];
                    [m_pView refreshTableHeights];
                }

                void SetFullyOnScreenOpen()
                {
                    [m_pView animateToOpenOnScreen];
                }

                void SetFullyOnScreenClosed()
                {
                    [m_pView animateToClosedOnScreen];
                }

                void SetOnScreenStateToIntermediateValue(float value)
                {
                    [m_pView setOnScreenStateToIntermediateValue:value];
                }

                void SetFullyOnScreen()
                {
                    [m_pView animateToClosedOnScreen];
                }

                void SetFullyOffScreen()
                {
                    [m_pView animateToRemovedFromScreen];
                }

                void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewClickedCallbacks.AddCallback(callback);
                }

                void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewClickedCallbacks.RemoveCallback(callback);
                }

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewOpenedCallbacks.AddCallback(callback);
                }

                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewOpenedCallbacks.RemoveCallback(callback);
                }

                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewClosedCallbacks.AddCallback(callback);
                }

                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewClosedCallbacks.RemoveCallback(callback);
                }

                void InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onDragStartedCallbacks.AddCallback(callback);
                }

                void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onDragStartedCallbacks.RemoveCallback(callback);
                }

                void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    m_onDragCallbacks.AddCallback(callback);
                }

                void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    m_onDragCallbacks.RemoveCallback(callback);
                }

                void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onDragCompletedCallbacks.AddCallback(callback);
                }

                void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onDragCompletedCallbacks.RemoveCallback(callback);
                }

                void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
                {
                    m_onItemSelectedCallbacks.AddCallback(callback);
                }

                void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
                {
                    m_onItemSelectedCallbacks.RemoveCallback(callback);
                }

                void HandleViewClicked()
                {
                    m_onViewClickedCallbacks.ExecuteCallbacks();
                }

                void HandleViewOpenCompleted()
                {
                    m_onViewOpenedCallbacks.ExecuteCallbacks();
                }

                void HandleViewCloseCompleted()
                {
                    m_onViewClosedCallbacks.ExecuteCallbacks();
                }

                void HandleDraggingViewStarted()
                {
                    m_onDragStartedCallbacks.ExecuteCallbacks();
                }

                void HandleDraggingViewInProgress(float progress)
                {
                    m_onDragCallbacks.ExecuteCallbacks(progress);
                }

                void HandleDraggingViewCompleted()
                {
                    m_onDragCompletedCallbacks.ExecuteCallbacks();
                }

                void HandleItemSelected(int sectionIndex, int itemIndex)
                {
                    m_onItemSelectedCallbacks.ExecuteCallbacks(sectionIndex, itemIndex);
                }

                bool CallBeginDrag()
                {
                    Eegeo_ASSERT(m_pTryDragFunc != NULL, "No drag function registered");
                    return (*m_pTryDragFunc)();
                }
            };
        }
    }

}
