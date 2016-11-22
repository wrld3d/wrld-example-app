// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include <string>

#include "ISettingsMenuView.h"
#include "IMenuView.h"
#include "IMenuSectionViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewImpl;

            class SettingsMenuView : public Menu::View::IMenuView, public ISettingsMenuView
            {
            private:
                SettingsMenuViewImpl* m_pImpl;

            public:
                SettingsMenuView(const std::shared_ptr<WindowsNativeState>& nativeState,
                                  const std::string& viewClassName);

                ~SettingsMenuView();
                
                void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function);
                void ClearTryDragFunc();

                float GetAnimationProgress() const;
                bool IsAnimating() const;
                bool IsTableAnimating() const;
                void UpdateAnimation(float dt);
                void UpdateTableAnimation(float dt);

                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);
                
                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();
                void SetFullyOnScreenOpen();
                void SetFullyOnScreenClosed();

                void SetTableCanInteract(bool canInteract);

                void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback);

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
            };
        }
    }
}
