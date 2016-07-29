// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinOnMapView.h"
#include "AndroidNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapView: public IWorldPinOnMapView
            {
            public:
                WorldPinOnMapView(AndroidNativeState& nativeState, float pinDiameter);
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

                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;
                const float m_pinOffset;
                bool m_showingEnlargedPin;

                Eegeo::Helpers::CallbackCollection0 m_selectedCallbacks;
            };
        }
    }
}
