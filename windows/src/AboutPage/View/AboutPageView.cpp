// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageView::AboutPageView(WindowsNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.AboutPageView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this)));
                
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mDisplayContent.SetupMethod(m_uiViewClass, m_uiView, "DisplayContent");
                mOpenAboutPage.SetupMethod(m_uiViewClass, m_uiView, "OpenAboutPage");
                mDismissAboutPage.SetupMethod(m_uiViewClass, m_uiView, "DismissAboutPage");
            }

            AboutPageView::~AboutPageView()
            {
                mDestroy();
            }

            void AboutPageView::CloseTapped()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void AboutPageView::Open()
            {
                mOpenAboutPage();
            }

            void AboutPageView::Close()
            {
                mDismissAboutPage();
            }

            void AboutPageView::SetContent(const std::string& content)
            {
                mDisplayContent(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(content));
            }

            void AboutPageView::ShowHiddenText()
            {
                m_logoLongPressCallbacks.ExecuteCallbacks();
            }

            void AboutPageView::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void AboutPageView::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void AboutPageView::InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_logoLongPressCallbacks.AddCallback(callback);
            }

            void AboutPageView::RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_logoLongPressCallbacks.RemoveCallback(callback);
            }
        }
    }
}
