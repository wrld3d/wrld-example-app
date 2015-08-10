// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinOnMapView.h"
#include "WorldPinOnMapView.h"
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

                WorldPinOnMapViewInterop(WorldPinOnMapView* pView)
                    : m_pView(pView)
                {
                }

                void Open(const std::string& title,
                          const std::string& subtitle,
                          const std::string& ratingsImage,
                          const int reviewCount,
                          float modality);
                void Close();
                void UpdateScreenLocation(float posX, float posY);
                void UpdateScreenState(float screenState);

                void OnSelected();
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                WorldPinOnMapView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_selectedCallbacks;
            };
        }
    }
}
