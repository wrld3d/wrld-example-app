// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMath.h"

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
                                       Eegeo::dv3 ecefTarget)
                        : m_ecefOrigin(ecefOrigin)
                        , m_ecefTarget(ecefTarget)
                        {
                            
                        }
                        
                        TweetStateData()
                        : m_ecefOrigin(0.0, 0.0, 0.0)
                        , m_ecefTarget(0.0, 0.0, 0.0)
                        {
                            
                        }
                        
                        Eegeo::dv3 m_ecefOrigin;
                        Eegeo::dv3 m_ecefTarget;
                    };
                }
            }
        }
    }
}