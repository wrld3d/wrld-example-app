// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "AttractModeOverlayView.h"
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
                                                           ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                                           ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                           ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pVirtualKeyboard,
                                                           ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
                : m_messageBus(messageBus)
                , m_appModeChangedCallback(this, &AttractModeOverlayView::OnAppModeChanged)
                , m_nativeState(nativeState)
                , m_searchMenuViewModel(searchMenuViewModel)
                , m_settingsMenuViewModel(settingsMenuViewModel)
                , m_myPinCreationDetailsViewModel(myPinCreationDetailsViewModel)
                , m_pVirtualKeyboard(pVirtualKeyboard)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.AttractModeOverlayView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mOnAttractModeStart.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStart");
                mOnAttractModeStop.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStop");
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");

                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }

            AttractModeOverlayView::~AttractModeOverlayView()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                mDestroy();
            }

            void AttractModeOverlayView::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode)
                {
                    m_myPinCreationDetailsViewModel.Close();
                    m_searchMenuViewModel.RemoveFromScreen();
                    m_settingsMenuViewModel.RemoveFromScreen();
                    if (m_pVirtualKeyboard != nullptr)
                    {
                        m_pVirtualKeyboard->HideVirtualKeyboard();
                    }
                    mOnAttractModeStart();
                }
                else
                {
                    m_searchMenuViewModel.AddToScreen();
                    m_settingsMenuViewModel.AddToScreen();
                    mOnAttractModeStop();
                }
            }
        }
    }
}
