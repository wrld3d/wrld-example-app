// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationService.h"
#include "InteriorHeightHelpers.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        IndoorAtlasLocationService::IndoorAtlasLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                                               const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
        : m_defaultLocationService(defaultLocationService)
        , m_environmentFlatteningService(environmentFlatteningService)
        , m_interiorInteractionModel(interiorInteractionModel)
        , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
        , m_floorIndex(0)
        {
        }
        
        const bool IndoorAtlasLocationService::GetIsAuthorized() const
        {
            return true;
        }
        
        bool IndoorAtlasLocationService::IsIndoors()
        {
            return true;
        }
        
        bool IndoorAtlasLocationService::GetIndoorID(int& indoorID)
        {
            return false;
        }
        
        bool IndoorAtlasLocationService::GetLocation(Eegeo::Space::LatLong& latLong)
        {
            latLong.SetLatitude(m_latLong.GetLatitude());
            latLong.SetLongitude(m_latLong.GetLongitude());
            return true;
        }
        
        bool IndoorAtlasLocationService::GetAltitude(double& altitude)
        {
            const Eegeo::Resources::Interiors::InteriorsModel* interiorModel = m_interiorInteractionModel.GetInteriorModel();
            if(interiorModel)
            {
                altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(*interiorModel,
                                                                                                                                 m_floorIndex,
                                                                                                                                 m_environmentFlatteningService.GetCurrentScale());
                return true;
            }
            
            return false;
        }
        
        bool IndoorAtlasLocationService::GetFloorIndex(int& floorIndex)
        {
            floorIndex = m_floorIndex;
            return true;
        }
        
        bool IndoorAtlasLocationService::GetHorizontalAccuracy(double& accuracy)
        {
            return false;
        }
        
        bool IndoorAtlasLocationService::GetHeadingDegrees(double& headingDegrees)
        {
            return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
        }
        
        void IndoorAtlasLocationService::StopListening()
        {
        }
        
        void IndoorAtlasLocationService::SetLocation(Eegeo::Space::LatLong &latLong)
        {
            m_latLong = latLong;
        }
        
        void IndoorAtlasLocationService::SetFloorIndex(int floorIndex)
        {
            m_floorIndex = floorIndex;
        }
    }
}