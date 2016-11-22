// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewImpl::AboutPageViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
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

            AboutPageViewImpl::~AboutPageViewImpl()
            {
                mDestroy();
            }

            void AboutPageViewImpl::CloseTapped()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void AboutPageViewImpl::Open()
            {
                mOpenAboutPage();
            }

            void AboutPageViewImpl::Close()
            {
                mDismissAboutPage();
            }

            void AboutPageViewImpl::SetContent(const std::string& content)
            {
                mDisplayContent(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(content));
            }

            void AboutPageViewImpl::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void AboutPageViewImpl::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}
