// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassView.h"
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
            CompassView::CompassView(WindowsNativeState& nativeState,
                bool isInKioskMode)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.CompassView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid, System::Boolean::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this), gcnew System::Boolean(isInKioskMode)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mShowGpsDisabledView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsDisabledView");
                mShowGpsFollowView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsFollowView");
                mShowGpsCompassModeView.SetupMethod(m_uiViewClass, m_uiView, "ShowGpsCompassModeView");
                mNotifyGpsUnauthorized.SetupMethod(m_uiViewClass, m_uiView, "NotifyGpsUnauthorized");
                mUpdateHeading.SetupMethod(m_uiViewClass, m_uiView, "UpdateHeading");
                mAnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
                mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
                mSetRotationHighlight.SetupMethod(m_uiViewClass, m_uiView, "SetRotationHighlight");
            }

            CompassView::~CompassView()
            {
                mDestroy();
            }

            void CompassView::OnCycle()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void CompassView::ShowGpsDisabledView()
            {
                mShowGpsDisabledView();
            }

            void CompassView::ShowGpsFollowView()
            {
                mShowGpsFollowView();
            }

            void CompassView::ShowGpsCompassModeView()
            {
                mShowGpsCompassModeView();
            }

            void CompassView::NotifyGpsUnauthorized()
            {
                mNotifyGpsUnauthorized();
            }

            void CompassView::SetHeadingRadians(float heading)
            {
                mUpdateHeading(heading);
            }

            void CompassView::SetOnScreenStateToIntermediateValue(float value)
            {
                mAnimateToIntermediateOnScreenState(value);
            }

            void CompassView::SetFullyOnScreen()
            {
                mAnimateToActive();
            }

            void CompassView::SetFullyOffScreen()
            {
                mAnimateToInactive();
            }

            void CompassView::SetRotationHighlight(bool shouldShowRotationHighlight)
            {
                mSetRotationHighlight(shouldShowRotationHighlight);
            }

            void CompassView::InsertCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void CompassView::RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
        }
    }
}
