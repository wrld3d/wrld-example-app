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
                        TweetStateData(Eegeo::dv3 ecefOrigin,
                                       Eegeo::dv3 ecefTarget,
                                       bool isInterior,
                                       WorldPins::SdkModel::WorldPinInteriorData interiorData,
                                       bool useBounds,
                                       Eegeo::Space::LatLong minBounds,
                                       Eegeo::Space::LatLong maxBounds)
                        : m_ecefOrigin(ecefOrigin)
                        , m_ecefTarget(ecefTarget)
                        , m_isInterior(isInterior)
                        , m_interiorData(interiorData)
                        , m_useBounds(useBounds)
                        , m_minBounds(minBounds)
                        , m_maxBounds(maxBounds)
                        {
                            if(m_useBounds)
                            {
                                if(m_minBounds.GetLatitude() > m_maxBounds.GetLatitude())
                                {
                                    double swapLat = m_maxBounds.GetLatitude();
                                    m_maxBounds.SetLatitude(m_minBounds.GetLatitude());
                                    m_minBounds.SetLatitude(swapLat);
                                }
                                if(m_minBounds.GetLongitude() > m_maxBounds.GetLongitude())
                                {
                                    double swapLong = m_maxBounds.GetLongitude();
                                    m_maxBounds.SetLongitude(m_minBounds.GetLongitude());
                                    m_minBounds.SetLongitude(swapLong);
                                }
                            }
                        }
                        
                        TweetStateData()
                        : m_ecefOrigin(0.0, 0.0, 0.0)
                        , m_ecefTarget(0.0, 0.0, 0.0)
                        , m_isInterior(false)
                        , m_interiorData()
                        , m_useBounds(false)
                        , m_minBounds(0,0)
                        , m_maxBounds(0,0)
                        {
                            
                        }
                        
                        Eegeo::dv3 m_ecefOrigin;
                        Eegeo::dv3 m_ecefTarget;
                        bool m_isInterior;
                        WorldPins::SdkModel::WorldPinInteriorData m_interiorData;
                        bool m_useBounds;
                        Eegeo::Space::LatLong m_minBounds;
                        Eegeo::Space::LatLong m_maxBounds;
                    };
                }
            }
        }
    }
}