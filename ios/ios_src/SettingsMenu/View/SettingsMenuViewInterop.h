// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"

#include "SettingsMenuViewIncludes.h"
#include "Types.h"
#include "MenuViewInterop.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewInterop : public ISettingsMenuView
            {
            public:
                SettingsMenuViewInterop(SettingsMenuView* pView)
                : m_menuInterop(pView)
                {
                }
                
                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
                {
                    m_menuInterop.SetTryDragFunc(function);
                }
                
                void ClearTryDragFunc()
                {
                    m_menuInterop.ClearTryDragFunc();
                }
                
                float GetAnimationProgress() const
                {
                    return m_menuInterop.GetAnimationProgress();
                }
                
                bool IsAnimating() const
                {
                    return m_menuInterop.IsAnimating();
                }
                
                bool IsTableAnimating() const
                {
                    return m_menuInterop.IsTableAnimating();
                }
                
                void UpdateAnimation(float dt)
                {
                    m_menuInterop.UpdateAnimation(dt);
                }
                
                void UpdateTableAnimation(float dt)
                {
                    m_menuInterop.UpdateTableAnimation(dt);
                }
                
                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
                {
                    m_menuInterop.UpdateMenuSectionViews(sections, contentsChanged);
                }
                
                void SetFullyOnScreenOpen()
                {
                    m_menuInterop.SetFullyOnScreenOpen();
                }
                
                void SetFullyOnScreenClosed()
                {
                    m_menuInterop.SetFullyOnScreenClosed();
                }
                
                void SetTableCanInteract(bool canInteract)
                {
                    m_menuInterop.SetTableCanInteract(canInteract);
                }
                
                void SetOnScreenStateToIntermediateValue(float value)
                {
                    m_menuInterop.SetOnScreenStateToIntermediateValue(value);
                }
                
                void SetFullyOnScreen()
                {
                    m_menuInterop.SetFullyOnScreen();
                }
                
                void SetFullyOffScreen()
                {
                    m_menuInterop.SetFullyOffScreen();
                }
                
                void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.InsertOnViewClicked(callback);
                }
                
                void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.RemoveOnViewClicked(callback);
                }
                
                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.InsertOnViewOpened(callback);
                }
                
                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.RemoveOnViewOpened(callback);
                }
                
                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.InsertOnViewClosed(callback);
                }
                
                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.RemoveOnViewClosed(callback);
                }
                
                void InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.InsertOnDragStarted(callback);
                }
                
                void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.RemoveOnDragStarted(callback);
                }
                
                void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    m_menuInterop.InsertOnDrag(callback);
                }
                
                void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
                {
                    m_menuInterop.RemoveOnDrag(callback);
                }
                
                void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.InsertOnDragCompleted(callback);
                }
                
                void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
                {
                    m_menuInterop.RemoveOnDragCompleted(callback);
                }
                
                void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
                {
                    m_menuInterop.InsertOnItemSelected(callback);
                }
                
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
                {
                    m_menuInterop.RemoveOnItemSelected(callback);
                }
            private:
                Menu::View::MenuViewInterop m_menuInterop;
            };
        }
    }
}
