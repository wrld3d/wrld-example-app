// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAboutPageView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageViewImpl;

            class AboutPageView : public IAboutPageView, private Eegeo::NonCopyable
            {
            private:
                AboutPageViewImpl* m_pImpl;

            public:
                AboutPageView(const std::shared_ptr<WindowsNativeState>& nativeState);

                ~AboutPageView();

                void CloseTapped();

                void Open();

                void Close();

                void SetContent(const std::string& content);

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
