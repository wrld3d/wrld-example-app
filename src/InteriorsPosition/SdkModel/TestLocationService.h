// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            class TestLocationService : public Eegeo::Location::ILocationService
            {
            public:
                const bool GetIsAuthorized() const;
                
                bool IsIndoors();
                bool GetIndoorID(int& indoorID);
                bool GetLocation(Eegeo::Space::LatLong& latLong);
                bool GetAltitude(double& altitude);
                bool GetFloorIndex(int& floorIndex);
                bool GetHorizontalAccuracy(double& accuracy);
                bool GetHeadingDegrees(double& headingDegrees);
                void StopListening();
            };
        }
    }
}