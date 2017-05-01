// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IFunc.h"
#include "IScreenControlView.h"
#include "IMenuSectionViewModel.h"

#include <vector>

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            typedef std::vector<IMenuSectionViewModel*> TSections;

            class IMenuView : public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~IMenuView() { };

                virtual void SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function) = 0;
                virtual void ClearTryDragFunc() = 0;

                virtual float GetAnimationProgress() const = 0;
                virtual bool IsAnimating() const = 0;
                virtual bool IsTableAnimating() const = 0;
                virtual void UpdateAnimation(float dt) = 0;
                virtual void UpdateTableAnimation(float dt) = 0;

                virtual void UpdateMenuSectionViews(TSections& sections, bool contentsChanged) = 0;

                virtual void SetFullyOnScreenOpen() = 0;
                virtual void SetFullyOnScreenClosed() = 0;

                virtual void SetTableCanInteract(bool canInteract) = 0;

                virtual void InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback) = 0;
                virtual void RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback) = 0;

                virtual void InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback) = 0;
                virtual void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback) = 0;
                
                virtual void ToggleSection(int sectionIndex) = 0;
            };
        }
    }
}
