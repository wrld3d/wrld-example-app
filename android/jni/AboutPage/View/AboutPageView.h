// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAboutPageView.h"
#include "AndroidNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageView : public IAboutPageView, private Eegeo::NonCopyable
            {
            private:
            	const std::shared_ptr<AndroidNativeState> m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                AboutPageView(const std::shared_ptr<AndroidNativeState>& nativeState);

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
