// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModel.h"
#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "TerrainHeightProvider.h"
#include "InteriorInteractionModel.h"
#include "InteriorHeightHelpers.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorsModel.h"
#include "EarthConstants.h"
#include "ISenionLocationService.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModel::GpsMarkerModel(ExampleApp::SenionLocation::SdkModel::ISenionLocationService& locationService,
                                           Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                           const bool interiorsAffectedByFlattening)
            : m_locationService(locationService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_hasLocation(false)
            , m_currentLocationEcef(Eegeo::dv3::Zero())
            , m_interiorsAffectedByFlattening(interiorsAffectedByFlattening)
            {
                
            }
            
            GpsMarkerModel::~GpsMarkerModel()
            {
                
            }
            
            bool GpsMarkerModel::UpdateGpsPosition()
            {
                Eegeo::Space::LatLong latLong(0,0);
                if(!m_locationService.GetLocation(latLong))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                float terrainHeight;
                Eegeo::dv3 ecefPositionFlat = latLong.ToECEF();
                if(!m_terrainHeightProvider.TryGetHeight(ecefPositionFlat, 1, terrainHeight))
                {
                    m_hasLocation = false;
                    return false;
                }
                
                m_currentLocationEcef = ecefPositionFlat + (ecefPositionFlat.Norm() * terrainHeight);
                m_hasLocation = true;
                return true;
            }
            
            void GpsMarkerModel::GetFinalEcefPosition(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlattening,
                                                      Eegeo::dv3& out_position)
            {
                float terrainHeight = 0.0f;
                const bool inInterior = m_interiorInteractionModel.HasInteriorModel();
                
                if (inInterior && m_locationService.isSenionMode() == true)
                {
                    Eegeo::Space::LatLong latlong = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                    GetServiceLocation(latlong);
                    
                    const int currentFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                    out_position = Eegeo::Space::LatLongAltitude::FromDegrees(latlong.GetLatitudeInDegrees(), latlong.GetLongitudeInDegrees(), (currentFloor * Helpers::InteriorHeightHelpers::INTERIOR_FLOOR_HEIGHT) + Helpers::InteriorHeightHelpers::INTERIOR_AVATAR_OFFSET).ToECEF();
                    
                }
                else if(inInterior)
                {
                    const int currentFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                    
                    float floorOffset = Helpers::InteriorHeightHelpers::INTERIOR_FLOOR_HEIGHT*currentFloor;
                    terrainHeight = interiorModel.GetTangentSpaceBounds().GetMin().y;
                    
                    if(m_interiorsAffectedByFlattening)
                    {
                        out_position = m_currentLocationEcef.Norm() * (Eegeo::Space::EarthConstants::Radius + terrainHeight + floorOffset);
                        out_position = environmentFlattening.GetScaledPointEcef(out_position, environmentFlattening.GetCurrentScale());
                    }
                    else
                    {
                        out_position = m_currentLocationEcef.Norm() * (Eegeo::Space::EarthConstants::Radius + terrainHeight);
                        out_position = environmentFlattening.GetScaledPointAboveGroundEcef(out_position, floorOffset, environmentFlattening.GetCurrentScale());
                    }
                }
                else
                {
                    out_position = environmentFlattening.GetScaledPointEcef(m_currentLocationEcef, environmentFlattening.GetCurrentScale());
                }
            }
            void GpsMarkerModel::GetServiceLocation(Eegeo::Space::LatLong &latLong){
                m_locationService.GetLocation(latLong);
            }

        }
    }
}