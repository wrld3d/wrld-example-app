// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAboutPageView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageView : public IAboutPageView, private Eegeo::NonCopyable
            {
            private:
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<System::String^> mDisplayContent;
                Helpers::ReflectionHelpers::Method<void> mOpenAboutPage;
                Helpers::ReflectionHelpers::Method<void> mDismissAboutPage;

                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                Eegeo::Helpers::CallbackCollection0 m_logoLongPressCallbacks;

            public:
                AboutPageView(WindowsNativeState& nativeState);

                ~AboutPageView();

                void CloseTapped();

                void Open();

                void Close();

                void SetContent(const std::string& content);

                void ShowHiddenText();

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
