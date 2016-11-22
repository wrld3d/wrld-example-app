// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinOnMapView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapViewImpl;

            class WorldPinOnMapView: public IWorldPinOnMapView
            {
            public:
                WorldPinOnMapView(const std::shared_ptr<WindowsNativeState>& nativeState, 
                                  const std::shared_ptr<ApplicationConfig::ApplicationConfiguration>& appConfig);
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
                WorldPinOnMapViewImpl* m_pImpl;
            };
        }
    }
}
