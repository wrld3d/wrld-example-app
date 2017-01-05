// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IAppModeModel.h"
#include "ReflectionHelpers.h"
#include "AttractModeOverlayView.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace AttractModeOverlay
    {
        namespace View
        {
            AttractModeOverlayView::AttractModeOverlayView(WindowsNativeState& nativeState, AppModes::SdkModel::IAppModeModel& appModeModel)
                : m_nativeState(nativeState)
                , m_appModeChangedCallback(this, &AttractModeOverlayView::OnAppModeChanged)
                , m_appModeModel(appModeModel)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.AttractModeOverlayView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mOnAttractModeStart.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStart");
                mOnAttractModeStop.SetupMethod(m_uiViewClass, m_uiView, "OnAttractModeStop");
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
            }

            AttractModeOverlayView::~AttractModeOverlayView()
            {
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                mDestroy();
            }

            void AttractModeOverlayView::OnAppModeChanged()
            {
                if (m_appModeModel.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode)
                {
                    mOnAttractModeStart();
                }
                else
                {
                    mOnAttractModeStop();
                }
            }
        }
    }
}
