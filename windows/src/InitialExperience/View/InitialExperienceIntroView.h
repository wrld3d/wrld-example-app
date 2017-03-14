// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceIntroView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "WindowsNativeState.h"
#include "BidirectionalBus.h"
#include "ReflectionHelpers.h"
#include "Types.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroView : public IInitialExperienceIntroView
            {
            public:

                InitialExperienceIntroView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
                ~InitialExperienceIntroView();

                void Show();
                void Dismiss();
                void OnDismiss();

                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);

                void ShowExitIUX();
                void DismissExitIUX();

            private:
                WindowsNativeState& m_nativeState;
                //jclass m_uiViewClass;
                //jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mShowExitIUX;
                Helpers::ReflectionHelpers::Method<void> mDismissExitIUX;
            };
        }
    }
}
