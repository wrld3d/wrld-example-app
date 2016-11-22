// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#using "System.dll"
#include <vcclr.h>

#include "WorldPinOnMapViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ImagePathHelpers.h"
#include "ReflectionHelpers.h"
#include "IWorldPinsInFocusModel.h"
#include "SearchVendorNames.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapViewImpl::WorldPinOnMapViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState, const std::shared_ptr<ApplicationConfig::ApplicationConfiguration>& appConfig)
                : m_nativeState(nativeState)
                , m_pinOffset(appConfig->PinDiameter() * Helpers::ImageHelpers::GetPixelScale())
                , m_largePinFocus(false)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.WorldPinOnMapView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid, float::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this), m_pinOffset));

               mShow.SetupMethod(m_uiViewClass, m_uiView, "Show");
               mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
               mUpdateScreenLocation.SetupMethod(m_uiViewClass, m_uiView, "UpdateScreenLocation");
               mUpdateScreenVisibility.SetupMethod(m_uiViewClass, m_uiView, "UpdateScreenVisibility");
            }

            WorldPinOnMapViewImpl::~WorldPinOnMapViewImpl()
            {
                
            }

            void WorldPinOnMapViewImpl::Open(const WorldPins::SdkModel::IWorldPinsInFocusModel& worldPinsInFocusModel,
                    float modality)
            {
                m_largePinFocus = worldPinsInFocusModel.GetVendor() == ExampleApp::Search::InteriorVendorName;
               mShow(ConvertUTF8ToManagedString(worldPinsInFocusModel.GetTitle()),
                     ConvertUTF8ToManagedString(worldPinsInFocusModel.GetSubtitle()),
                     ConvertUTF8ToManagedString(worldPinsInFocusModel.GetRatingsImage()),
                     worldPinsInFocusModel.GetReviewCount(),
                     modality);
            }

            void WorldPinOnMapViewImpl::Close()
            {
                mDismiss();
            }

            void WorldPinOnMapViewImpl::UpdateScreenLocation(float posX, float posY)
            {
                float offsetY = posY - (m_largePinFocus ? m_pinOffset*1.5f : m_pinOffset);
                mUpdateScreenLocation(posX, offsetY);
            }

            void WorldPinOnMapViewImpl::UpdateScreenState(float screenState)
            {
                mUpdateScreenVisibility(screenState);
            }

            void WorldPinOnMapViewImpl::OnSelected()
            {
                m_selectedCallbacks.ExecuteCallbacks();
            }

            void WorldPinOnMapViewImpl::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_selectedCallbacks.AddCallback(callback);
            }

            void WorldPinOnMapViewImpl::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_selectedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
