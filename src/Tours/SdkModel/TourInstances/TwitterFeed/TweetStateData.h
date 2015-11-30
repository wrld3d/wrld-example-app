// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

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
                                       WorldPins::SdkModel::WorldPinInteriorData interiorData)
                        : m_ecefOrigin(ecefOrigin)
                        , m_ecefTarget(ecefTarget)
                        , m_isInterior(isInterior)
                        , m_interiorData(interiorData)
                        {
                            
                        }
                        
                        TweetStateData()
                        : m_ecefOrigin(0.0, 0.0, 0.0)
                        , m_ecefTarget(0.0, 0.0, 0.0)
                        , m_isInterior(false)
                        , m_interiorData()
                        {
                            
                        }
                        
                        Eegeo::dv3 m_ecefOrigin;
                        Eegeo::dv3 m_ecefTarget;
                        bool m_isInterior;
                        WorldPins::SdkModel::WorldPinInteriorData m_interiorData;
                    };
                }
            }
        }
    }
}