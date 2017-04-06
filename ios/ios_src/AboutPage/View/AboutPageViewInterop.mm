// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewInterop.h"
#include "AboutPageView.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewInterop::AboutPageViewInterop(AboutPageView* pView) : m_pView(pView)
            {
            }

            void AboutPageViewInterop::CloseTapped()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void AboutPageViewInterop::Open()
            {
                [m_pView setFullyActive];
            }

            void AboutPageViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }

            void AboutPageViewInterop::SetContent(const std::string& content)
            {
                [m_pView setContent:&content];
            }
            
            void AboutPageViewInterop::ShowHiddenText()
            {
                m_hiddenTextCallbacks.ExecuteCallbacks();
            }

            void AboutPageViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void AboutPageViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void AboutPageViewInterop::InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_hiddenTextCallbacks.AddCallback(callback);
            }
            
            void AboutPageViewInterop::RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_hiddenTextCallbacks.RemoveCallback(callback);
            }
        }
    }
}
