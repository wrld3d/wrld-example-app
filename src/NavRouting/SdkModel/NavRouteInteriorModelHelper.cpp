// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteInteriorModelHelper.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            bool NavRouteInteriorModelHelper::TryGetIndoorMapFloorId(const Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                     const std::string& indoorMapId,
                                                                     const int floorIndex,
                                                                     int& out_floorId)
            {
                out_floorId = 0;
                if (!interiorsModelRepository.HasInterior(indoorMapId))
                {
                    return false;
                }

                const auto& interiorsModel = interiorsModelRepository.GetInterior(indoorMapId);

                if (floorIndex < 0 || floorIndex >= interiorsModel.GetFloorCount())
                {
                    return false;
                }

                const auto& interiorsFloorModel = interiorsModel.GetFloorAtIndex(floorIndex);
                out_floorId = interiorsFloorModel.GetFloorNumber();
                return true;
            }
            
            bool NavRouteInteriorModelHelper::TryGetIndoorMapFloorName(const Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                       const std::string& indoorMapId,
                                                                       const int indoorMapFloorId,
                                                                       std::string& out_indoorMapFloorName)
            {
                if (!interiorsModelRepository.HasInterior(indoorMapId))
                {
                    return false;
                }
                
                return TryGetIndoorMapFloorName(interiorsModelRepository.GetInterior(indoorMapId), indoorMapFloorId, out_indoorMapFloorName);
            }
            
            bool NavRouteInteriorModelHelper::TryGetIndoorMapFloorName(const Eegeo::Resources::Interiors::InteriorsModel& interiorsModel,
                                                                       const int indoorMapFloorId,
                                                                       std::string& out_indoorMapFloorName)
            {
                const int floorIndex = interiorsModel.FindFloorIndexWithFloorNumber(indoorMapFloorId);
                
                if (floorIndex < 0 || floorIndex >= interiorsModel.GetFloorCount())
                {
                    return false;
                }
                
                const auto& floorModel = interiorsModel.GetFloorAtIndex(floorIndex);
                out_indoorMapFloorName = floorModel.GetFloorName();
                return true;
            }
        }
    }
}
