// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "AttractModeOverlayView.h"
#include "AttractModeStates.h"
#include "IAppModeModel.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "ReflectionHelpers.h"
#include "VirtualKeyboardView.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace AttractModeOverlay
    {
        namespace View
        {
            AttractModeOverlayView::AttractModeOverlayView(WindowsNativeState& nativeState,
                                                           ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pVirtualKeyboard,
                                                           ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
                : m_messageBus(messageBus)
                , m_appModeChangedCallback(this, &AttractModeOverlayView::OnAppModeChanged)
                , m_attractModeStateChangedCallback(this, &AttractModeOverlayView::OnAttractModeStateChanged)
                , m_nativeState(nativeState)
                , m_myPinCreationDetailsViewModel(myPinCreationDetailsViewModel)
                , m_pVirtualKeyboard(pVirtualKeyboard)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.AttractModeOverlayView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mOnAttractModeStart.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStart");
                mOnAttractModeStop.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStop");
                mOnAttractModeExiting.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeExiting");
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");

                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_attractModeStateChangedCallback);
            }

            AttractModeOverlayView::~AttractModeOverlayView()
            {
                m_messageBus.UnsubscribeUi(m_attractModeStateChangedCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                mDestroy();
            }

            void AttractModeOverlayView::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode)
                {
                    m_myPinCreationDetailsViewModel.Close();
                    if (m_pVirtualKeyboard != nullptr)
                    {
                        m_pVirtualKeyboard->HideVirtualKeyboard();
                    }
                    mOnAttractModeStart();
                }
                else
                {
                    mOnAttractModeStop();
                }
            }

            void AttractModeOverlayView::OnAttractModeStateChanged(const AttractMode::AttractModeStateChangedMessage& message)
            {
                if (message.State() == AttractMode::SdkModel::States::State::ExitState)
                {
                    mOnAttractModeExiting();
                }
            }
        }
    }
}
