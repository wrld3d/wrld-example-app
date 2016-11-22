// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

#include "ReflectionHelpers.h"

#include <msclr\marshal_cppstd.h>

using namespace ExampleApp::Helpers::ReflectionHelpers;

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsViewImpl::MyPinCreationDetailsViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.MyPinCreationDetailsView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(System::IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew System::IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mShow.SetupMethod(m_uiViewClass, m_uiView, "Show");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");

                mGetTitle.SetupMethod(m_uiViewClass, m_uiView, "GetTitle");
                mGetDescription.SetupMethod(m_uiViewClass, m_uiView, "GetDescription");
                mGetShouldShare.SetupMethod(m_uiViewClass, m_uiView, "GetShouldShare");
                mGetImageBuffer.SetupMethod(m_uiViewClass, m_uiView, "GetImageBuffer");
                mGetImageBufferSize.SetupMethod(m_uiViewClass, m_uiView, "GetImageBufferSize");
            }

            MyPinCreationDetailsViewImpl::~MyPinCreationDetailsViewImpl()
            {
                mDestroy();
            }

            void MyPinCreationDetailsViewImpl::Open()
            {
                mShow();
            }

            void MyPinCreationDetailsViewImpl::Close()
            {
                mDismiss();
            }

            void MyPinCreationDetailsViewImpl::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsViewImpl::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsViewImpl::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsViewImpl::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationDetailsViewImpl::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsViewImpl::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            std::string MyPinCreationDetailsViewImpl::GetTitle() const
            {
                System::String^ str = mGetTitle.Call<System::String^>();
                return msclr::interop::marshal_as<std::string>(str);
            }

            std::string MyPinCreationDetailsViewImpl::GetDescription() const
            {
                System::String^ str = mGetDescription.Call<System::String^>();
                return msclr::interop::marshal_as<std::string>(str);
            }

            bool MyPinCreationDetailsViewImpl::ShareSelected() const
            {
                return (bool)mGetShouldShare.Call<System::Boolean^>();
            }

            Byte* MyPinCreationDetailsViewImpl::GetImageBuffer() const
            {
                array<System::Byte>^ arr = mGetImageBuffer.Call<array<System::Byte>^>();

                if (arr == nullptr)
                    return NULL;

                //WHO THE HELL DELETES THIS??
                Byte* data = new Byte[arr->Length];

                for (int i = 0; i < arr->Length; ++i)
                {
                    data[i] = static_cast<Byte>(arr[i]);
                }

                return data;
            }

            size_t MyPinCreationDetailsViewImpl::GetImageSize() const
            {
                return (int)mGetImageBufferSize.Call<System::Int32^>();
            }

            void MyPinCreationDetailsViewImpl::ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings)
            {

            }
        }
    }
}

