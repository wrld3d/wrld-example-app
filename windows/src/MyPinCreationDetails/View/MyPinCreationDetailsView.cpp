// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsView.h"
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
            MyPinCreationDetailsView::MyPinCreationDetailsView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus, bool isInKioskMode)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
                , m_appModeChangedCallback(this, &MyPinCreationDetailsView::OnAppModeChanged)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.MyPinCreationDetailsView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(System::IntPtr::typeid, System::Boolean::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew System::IntPtr(this), gcnew System::Boolean(isInKioskMode)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mShow.SetupMethod(m_uiViewClass, m_uiView, "Show");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");

                mGetTitle.SetupMethod(m_uiViewClass, m_uiView, "GetTitle");
                mGetDescription.SetupMethod(m_uiViewClass, m_uiView, "GetDescription");
                mGetShouldShare.SetupMethod(m_uiViewClass, m_uiView, "GetShouldShare");
                mGetImageBuffer.SetupMethod(m_uiViewClass, m_uiView, "GetImageBuffer");
                mGetImageBufferSize.SetupMethod(m_uiViewClass, m_uiView, "GetImageBufferSize");
                mResetTutorialViewCount.SetupMethod(m_uiViewClass, m_uiView, "ResetTutorialViewCount");

                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }

            MyPinCreationDetailsView::~MyPinCreationDetailsView()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);

                mDestroy();
            }

            void MyPinCreationDetailsView::Open()
            {
                mShow();
            }

            void MyPinCreationDetailsView::Close()
            {
                mDismiss();
            }

            void MyPinCreationDetailsView::OnConfirmed()
            {
                m_confirmedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsView::OnDismissed()
            {
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void MyPinCreationDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void MyPinCreationDetailsView::InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.AddCallback(callback);
            }

            void MyPinCreationDetailsView::RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_confirmedCallbacks.RemoveCallback(callback);
            }

            std::string MyPinCreationDetailsView::GetTitle() const
            {
                System::String^ str = mGetTitle.Call<System::String^>();
                return msclr::interop::marshal_as<std::string>(str);
            }

            std::string MyPinCreationDetailsView::GetDescription() const
            {
                System::String^ str = mGetDescription.Call<System::String^>();
                return msclr::interop::marshal_as<std::string>(str);
            }

            bool MyPinCreationDetailsView::ShareSelected() const
            {
                return (bool)mGetShouldShare.Call<System::Boolean^>();
            }

            Byte* MyPinCreationDetailsView::GetImageBuffer() const
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

            size_t MyPinCreationDetailsView::GetImageSize() const
            {
                return (int)mGetImageBufferSize.Call<System::Int32^>();
            }

            void MyPinCreationDetailsView::ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings)
            {

            }

			void MyPinCreationDetailsView::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
			{
				if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode)
				{
					mResetTutorialViewCount();
				}
			}
        }
    }
}

