// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;
using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewImpl::CompassViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.CompassView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mShowGpsDisabledView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsDisabledView");
                mShowGpsFollowView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsFollowView");
                mShowGpsCompassModeView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsCompassModeView");
                mNotifyGpsUnauthorized.SetupMethod(m_uiViewClass, m_uiView, "NotifyGpsUnauthorized");
                mUpdateHeading.SetupMethod(m_uiViewClass, m_uiView, "UpdateHeading");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
            }

            CompassViewImpl::~CompassViewImpl()
            {
                mDestroy();
            }

            void CompassViewImpl::OnCycle()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void CompassViewImpl::ShowGpsDisabledView()
            {
                mShowGpsDisabledView();
            }

            void CompassViewImpl::ShowGpsFollowView()
            {
                mShowGpsFollowView();
            }

            void CompassViewImpl::ShowGpsCompassModeView()
            {
                mShowGpsCompassModeView();
            }

            void CompassViewImpl::NotifyGpsUnauthorized()
            {
                mNotifyGpsUnauthorized();
            }

            void CompassViewImpl::SetHeadingRadians(float heading)
            {
                mUpdateHeading(heading);
            }

            void CompassViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void CompassViewImpl::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void CompassViewImpl::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }

            void CompassViewImpl::InsertCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void CompassViewImpl::RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}
