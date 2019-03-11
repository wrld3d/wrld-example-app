// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingHelpers.h"
#include "OfflineRouting.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Helpers
            {
                float SqrDistance(const Eegeo::dv3& a, const Eegeo::dv3& b)
                {
                    return static_cast<float>(a.SquareDistanceTo(b));
                }

                float Distance(const Eegeo::dv3& a, const Eegeo::dv3& b)
                {
                    return Eegeo::Math::Sqrtf(SqrDistance(a, b));
                }

                Eegeo::Space::LatLong GetLatLongFromEcef(const Eegeo::dv3& ecefPoint)
                {
                    return Eegeo::Space::LatLong::FromECEF(ecefPoint);
                }

                Eegeo::dv3 GetEcefPointFromLatlong(const Eegeo::Space::LatLong& point, const int floorId)
                {
                    return Eegeo::Space::LatLongAltitude::FromLatLong(point, floorId * RoutingEngine::INTERIOR_FLOOR_HEIGHT).ToECEF();
                }

                float GetSpeedForTransportationMode(Eegeo::Routes::Webservice::TransportationMode transportationMode)
                {
                    switch (transportationMode)
                    {
                        case Eegeo::Routes::Webservice::TransportationMode::Driving:
                            return RoutingEngine::DRIVING_SPEED_IN_METER_PER_SECOND;
                        default:
                            return RoutingEngine::WALKING_SPEED_IN_METER_PER_SECOND;
                    }
                }

                float GetDurationMultiplierForFeatureType(const std::string& featureType)
                {
                    if (featureType == "stairs")
                    {
                        return RoutingEngine::STAIRS_FEATURE_TYPE_DURATION_MULTIPLIER;
                    }

                    if (featureType == "escalator")
                    {
                        return RoutingEngine::ESCALATOR_FEATURE_TYPE_DURATION_MULTIPLIER;
                    }

                    if (featureType == "elevator")
                    {
                        return RoutingEngine::ELEVATOR_FEATURE_TYPE_DURATION_MULTIPLIER;
                    }

                    return 1;
                }
            }
        }
    }
}
