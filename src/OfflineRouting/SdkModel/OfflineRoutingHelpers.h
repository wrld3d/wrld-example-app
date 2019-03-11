// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include "VectorMath.h"
#include "RouteData.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Helpers
            {
                float SqrDistance(const Eegeo::dv3& a, const Eegeo::dv3& b);

                float Distance(const Eegeo::dv3& a, const Eegeo::dv3& b);

                Eegeo::Space::LatLong GetLatLongFromEcef(const Eegeo::dv3& ecefPoint);

                Eegeo::dv3 GetEcefPointFromLatlong(const Eegeo::Space::LatLong& point, const int floorId);

                float GetSpeedForTransportationMode(Eegeo::Routes::Webservice::TransportationMode transportationMode);

                float GetDurationMultiplierForFeatureType(const std::string& featureType);
            }
        }
    }
}
