// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinOnMapView.h"
#include "WorldPinOnMapViewContainer.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapViewInterop : public IWorldPinOnMapView
            {
            public:

                WorldPinOnMapViewInterop(WorldPinOnMapViewContainer* pView)
                    : m_pView(pView)
                {
                }

                void Open(const WorldPins::SdkModel::IWorldPinsInFocusModel& worldPinsInFocusModel, float modality);
                void Close();
                void UpdateScreenLocation(float posX, float posY);
                void UpdateScreenState(float screenState);
                void UpdateScreenStateAndVisibility(float screenState);


                void OnSelected();
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                WorldPinOnMapViewContainer* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_selectedCallbacks;
            };
        }
    }
}
