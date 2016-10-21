// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorHeightHelpers.h"
#include "ILocationService.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "Bounds.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace InteriorNavigationHelpers
        {
            bool IsPositionInInterior(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                      Eegeo::Location::ILocationService& locationService)
            {
                Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0.0f, 0.0f);
                
                if(locationService.GetLocation(latLong) && interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorsModel = *interiorInteractionModel.GetInteriorModel();
                    const Eegeo::Geometry::Bounds3D& tangentBounds = interiorsModel.GetTangentSpaceBounds();
                    const Eegeo::dv3& boundsEcefOrigin = interiorsModel.GetTangentBasis().GetPointEcef();
                    float targetAltitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(interiorsModel, interiorInteractionModel.GetSelectedFloorIndex());
                    
                    Eegeo::Geometry::SingleSphere toleranceSphere;
                    const Eegeo::v3 reletaivePoint = (Eegeo::Space::LatLongAltitude::FromRadians(latLong.GetLatitude(),
                                                                                                 latLong.GetLongitude(),
                                                                                                 targetAltitude).ToECEF() - boundsEcefOrigin).ToSingle();
                    
                    toleranceSphere.centre = Eegeo::v3::MulRotate(reletaivePoint, interiorsModel.GetTangentBasis().GetEcefToTangentTransform());
                    toleranceSphere.radius = 10.0f;
                    
                    if(tangentBounds.intersectsSphere(toleranceSphere))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
}
