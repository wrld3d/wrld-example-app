// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsViewImpl::MyPinDetailsViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                :m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.MyPinDetailsView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mDisplay.SetupMethod(m_uiViewClass, m_uiView, "Display");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
            }

            MyPinDetailsViewImpl::~MyPinDetailsViewImpl()
            {
                mDestroy();
            }

            void MyPinDetailsViewImpl::OnDismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsViewImpl::OnRemove()
            {
                m_removePinCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsViewImpl::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinDetailsViewImpl::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsViewImpl::InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.AddCallback(callback);
            }

            void MyPinDetailsViewImpl::RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsViewImpl::OpenWithModel(
                    const std::string& title,
                    const std::string& description,
                    const std::string& imagePath)
            {
                mDisplay(gcnew System::String(title.c_str()), gcnew System::String(description.c_str()), gcnew System::String(imagePath.c_str()));
            }

            void MyPinDetailsViewImpl::Close()
            {
                mDismiss();
            }
        }
    }
}
