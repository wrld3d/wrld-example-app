// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStreamingVolume.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                class PreloadSphereVolume : public Eegeo::Streaming::IStreamingVolume
                {
                    Eegeo::dv3 m_ecefCentre;
                    double m_sphereVolumeRadius;

                public:
                    PreloadSphereVolume(double lat, double lon, double radius);

                    bool IntersectsKey(const Eegeo::Streaming::MortonKey& key,
                                       bool& canRefineIntersectedKey,
                                       double& intersectedNodeDepthSortSignedDistance);
                };
            }
        }
    }
}
