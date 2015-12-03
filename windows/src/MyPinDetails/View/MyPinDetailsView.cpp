// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsView::MyPinDetailsView(WindowsNativeState& nativeState)
                :m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.MyPinDetailsView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mDisplay.SetupMethod(m_uiViewClass, m_uiView, "Display");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
            }

            MyPinDetailsView::~MyPinDetailsView()
            {
                mDestroy();
            }

            void MyPinDetailsView::OnDismiss()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsView::OnRemove()
            {
                m_removePinCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsView::InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.AddCallback(callback);
            }

            void MyPinDetailsView::RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_removePinCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsView::OpenWithModel(
                    const std::string& title,
                    const std::string& description,
                    const std::string& imagePath)
            {
                mDisplay(gcnew System::String(title.c_str()), gcnew System::String(description.c_str()), gcnew System::String(imagePath.c_str()));
            }

            void MyPinDetailsView::Close()
            {
                mDismiss();
            }
        }
    }
}
