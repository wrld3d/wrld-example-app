// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPageViewIncludes.h"
#include "IAboutPageView.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageViewInterop : public IAboutPageView, private Eegeo::NonCopyable
            {
            private:
                AboutPageView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                Eegeo::Helpers::CallbackCollection0 m_hiddenTextCallbacks;

            public:
                AboutPageViewInterop(AboutPageView* pView);

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
