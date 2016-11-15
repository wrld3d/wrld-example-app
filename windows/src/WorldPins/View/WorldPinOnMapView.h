// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinOnMapView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapView: public IWorldPinOnMapView
            {
            public:
                WorldPinOnMapView(WindowsNativeState& nativeState, float pinDiameter);
                ~WorldPinOnMapView();

                void Open(const WorldPins::SdkModel::IWorldPinsInFocusModel& worldPinsInFocusModel,
                          float modality);
                void Close();
                void UpdateScreenLocation(float posX, float posY);
                void UpdateScreenState(float screenState);

                void OnSelected();
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                Helpers::ReflectionHelpers::Method<System::String^, System::String^,
                                                    System::String^, int, float> mShow;
                Helpers::ReflectionHelpers::Method<void> mDismiss;
                Helpers::ReflectionHelpers::Method<float, float> mUpdateScreenLocation;
                Helpers::ReflectionHelpers::Method<float> mUpdateScreenVisibility;
                
                WindowsNativeState& m_nativeState;
                const float m_pinOffset;
                bool m_largePinFocus;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_selectedCallbacks;
            };
        }
    }
}
