// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
#include "MenuViewIncludes.h"
#include "IFunc.h"
#include "ICallback.h"
#include "CallbackCollection.h"

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
                Eegeo::Helpers::CallbackCollection0 m_onViewClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenStartedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                Eegeo::Helpers::CallbackCollection2<int, int> m_onItemSelectedCallbacks;

            public:
                MenuViewInterop(MenuView* pView)
                    : m_pView(pView)
                {
                }

                void SetTableCanInteract(bool canInteract)
                {
                    [m_pView setTableCanInteract:canInteract];
                }

                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
                {
                    
                }

                void ClearTryDragFunc()
                {
                    
                }

                float GetAnimationProgress() const
                {
                    return [m_pView openOnScreenState];
                }

                bool IsAnimating() const
                {
                    return [m_pView isAnimating];
                }
                
                bool IsTableAnimating() const
                {
                    return [m_pView isTableAnimating];
                }
                
                void UpdateAnimation(float dt)
                {
                    [m_pView updateAnimation:dt];
                }
                
                void UpdateTableAnimation(float dt)
                {
                    [m_pView updateTableAnimation:dt];
                }
                
                void UpdateMenuSectionViews(TSections& sections, bool contentsChanged)
                {
                    [m_pView updateMenuSections:&sections];
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
                
                void InsertOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewOpenStartedCallbacks.AddCallback(callback);
                }
                
                void RemoveOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_onViewOpenStartedCallbacks.RemoveCallback(callback);
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
                    
                }

                void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    
                }

                void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    
                }

                void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    
                }

                void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    
                }

                void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    
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
                
                void HandleViewOpenStarted()
                {
                    m_onViewOpenStartedCallbacks.ExecuteCallbacks();
                }

                void HandleViewCloseCompleted()
                {
                    m_onViewClosedCallbacks.ExecuteCallbacks();
                }

                void HandleDraggingViewStarted()
                {
                    
                }

                void HandleDraggingViewInProgress(float progress)
                {
                    
                }

                void HandleDraggingViewCompleted()
                {
                    
                }

                void HandleItemSelected(int sectionIndex, int itemIndex)
                {
                    m_onItemSelectedCallbacks.ExecuteCallbacks(sectionIndex, itemIndex);
                }

                bool CallBeginDrag()
                {
                    return false;
                }

                void ToggleSection(int sectionIndex)
                {
                    [m_pView toggleSection:sectionIndex];
                }
            };
        }
    }

}
