// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"

#include <string>

#include "ReflectionHelpers.h"
#include "IMenuView.h"
#include "IMenuSectionViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuView : public Menu::View::IMenuView
            {
                typedef std::vector<Menu::View::IMenuSectionViewModel*> TSections;

            private:
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

            public:
                SettingsMenuView(WindowsNativeState& nativeState,
                                  const std::string& viewClassName);

                 void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function);
                 void ClearTryDragFunc();

                 void SetOnScreenStateToIntermediateValue(float value);
                 void SetFullyOnScreen();
                 void SetFullyOffScreen();

                 float GetAnimationProgress() const;
                 bool IsAnimating() const;
                 bool IsTableAnimating() const;
                 void UpdateAnimation(float dt);
                 void UpdateTableAnimation(float dt);

                 void UpdateMenuSectionViews(TSections& sections);

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
