// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PreloadSphereVolume.h"
#include "LatLongAltitude.h"
#include "CubeMapCellInfo.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                PreloadSphereVolume::PreloadSphereVolume(double lat, double lon, double radius)
                    : m_ecefCentre(Eegeo::Space::LatLong::FromDegrees(lat, lon).ToECEF())
                    , m_sphereVolumeRadius(radius)
                {

                }

                bool PreloadSphereVolume::IntersectsKey(const Eegeo::Streaming::MortonKey& key,
                                                        bool& canRefineIntersectedKey,
                                                        double& intersectedNodeDepthSortSignedDistance)
                {
                    intersectedNodeDepthSortSignedDistance = 0.0;

                    const Eegeo::Space::CubeMap::CubeMapCellInfo cellInfo(key);
                    const Eegeo::dv3 keyEcef = cellInfo.GetFaceCentreECEF();
                    const double distanceBetweenCellBoundingSphereAndVolumeSphere = (m_ecefCentre - keyEcef).Length();
                    const double cellWidth = key.WidthInMetres();
                    const double cellBoundingSphereRadius = std::sqrt((cellWidth*cellWidth) + (cellWidth*cellWidth));

                    if(distanceBetweenCellBoundingSphereAndVolumeSphere < (m_sphereVolumeRadius + cellBoundingSphereRadius))
                    {
                        canRefineIntersectedKey = true;
                        return true;
                    }

                    canRefineIntersectedKey = false;
                    return false;
                }
            }
        };
    }
}
