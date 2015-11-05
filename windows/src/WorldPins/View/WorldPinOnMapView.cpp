// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#using "System.dll"
#include <vcclr.h>

#include "WorldPinOnMapView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ImagePathHelpers.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapView::WorldPinOnMapView(WindowsNativeState& nativeState, float pinDiameter)
                : m_nativeState(nativeState)
                , m_pinOffset((pinDiameter * Helpers::ImageHelpers::GetPixelScale()) * 0.75f)
            {
                m_uiViewClass = GetTypeFromAssembly("ExampleAppWPF", "ExampleAppWPF.WorldPinOnMapView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid, float::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this), m_pinOffset));

               mShow.SetupMethod(m_uiViewClass, m_uiView, "Show");
               mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
               mUpdateScreenLocation.SetupMethod(m_uiViewClass, m_uiView, "UpdateScreenLocation");
               mUpdateScreenVisibility.SetupMethod(m_uiViewClass, m_uiView, "UpdateScreenVisibility");
            }

            WorldPinOnMapView::~WorldPinOnMapView()
            {
                
            }

            void WorldPinOnMapView::Open(const std::string& title,
                    const std::string& subtitle,
                    const std::string& ratingsImage,
                    const int reviewCount,
                    float modality)
            {
               mShow(ConvertUTF8ToManagedString(title), ConvertUTF8ToManagedString(subtitle), ConvertUTF8ToManagedString(ratingsImage), reviewCount, modality);
            }

            void WorldPinOnMapView::Close()
            {
                mDismiss();
            }

            void WorldPinOnMapView::UpdateScreenLocation(float posX, float posY)
            {
                float offsetY = posY - m_pinOffset;
                mUpdateScreenLocation(posX, offsetY);
            }

            void WorldPinOnMapView::UpdateScreenState(float screenState)
            {
                mUpdateScreenVisibility(screenState);
            }

            void WorldPinOnMapView::OnSelected()
            {
                m_selectedCallbacks.ExecuteCallbacks();
            }

            void WorldPinOnMapView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_selectedCallbacks.AddCallback(callback);
            }

            void WorldPinOnMapView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_selectedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
