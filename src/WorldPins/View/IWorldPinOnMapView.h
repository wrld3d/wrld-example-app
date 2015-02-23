// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class IWorldPinOnMapView
            {
            public:
                virtual ~IWorldPinOnMapView() {};

                virtual void Open(const std::string& title,
                                  const std::string& subtitle,
                                  float modality) = 0;
                virtual void Close() = 0;
                virtual void UpdateScreenLocation(float posX, float posY) = 0;
                virtual void UpdateScreenState(float screenState) = 0;

                virtual void OnSelected() = 0;
                virtual void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
