// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "CompassGpsMode.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class ICompassModel
            {
            public:

                virtual ~ICompassModel() {}

                virtual bool GetGpsModeActive() const = 0;

                virtual GpsMode::Values GetGpsMode() const = 0;

                virtual float GetHeadingRadians() const = 0;

                virtual float GetHeadingDegrees() const = 0;

                virtual void TryUpdateToNavigationServiceGpsMode(Eegeo::Location::NavigationService::GpsMode value) = 0;

                virtual void DisableGpsMode() = 0;

                virtual void CycleToNextGpsMode() = 0;

                virtual void InsertGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void RemoveGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void RemoveGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
