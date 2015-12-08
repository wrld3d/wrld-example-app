// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include "VectorMath.h"
#include "WorldPinInteriorData.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    struct TweetStateData
                    {
                    public:
                        TweetStateData(Eegeo::dv3 _ecefTarget,
                                       float _cameraDistanceToTarget,
                                       float _cameraTiltDegrees,
                                       bool _isInterior,
                                       WorldPins::SdkModel::WorldPinInteriorData _interiorData,
                                       bool _useBounds,
                                       Eegeo::Space::LatLong _minBounds,
                                       Eegeo::Space::LatLong _maxBounds)
                        : ecefTarget(_ecefTarget)
                        , cameraDistanceToTarget(_cameraDistanceToTarget)
                        , cameraTiltDegrees(_cameraTiltDegrees)
                        , isInterior(_isInterior)
                        , interiorData(_interiorData)
                        , useBounds(_useBounds)
                        , minBounds(_minBounds)
                        , maxBounds(_maxBounds)
                        {
                            if(useBounds)
                            {
                                if(minBounds.GetLatitude() > maxBounds.GetLatitude())
                                {
                                    double swapLat = maxBounds.GetLatitude();
                                    maxBounds.SetLatitude(minBounds.GetLatitude());
                                    minBounds.SetLatitude(swapLat);
                                }
                                if(minBounds.GetLongitude() > maxBounds.GetLongitude())
                                {
                                    double swapLong = maxBounds.GetLongitude();
                                    maxBounds.SetLongitude(minBounds.GetLongitude());
                                    minBounds.SetLongitude(swapLong);
                                }
                            }
                        }
                        
                        TweetStateData()
                        : ecefTarget(0.0, 0.0, 0.0)
                        , cameraDistanceToTarget(300.0f)
                        , cameraTiltDegrees(45.0f)
                        , isInterior(false)
                        , interiorData()
                        , useBounds(false)
                        , minBounds(0,0)
                        , maxBounds(0,0)
                        {
                            
                        }
                        
                        Eegeo::dv3 ecefTarget;
                        float cameraDistanceToTarget;
                        float cameraTiltDegrees;
                        bool isInterior;
                        WorldPins::SdkModel::WorldPinInteriorData interiorData;
                        bool useBounds;
                        Eegeo::Space::LatLong minBounds;
                        Eegeo::Space::LatLong maxBounds;
                    };
                }
            }
        }
    }
}