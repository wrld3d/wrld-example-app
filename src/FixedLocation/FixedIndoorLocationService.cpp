// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "FixedIndoorLocationService.h"
#include "LatLongAltitude.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorHeightHelpers.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"

namespace Eegeo
{
    namespace FixedLocation
    {
        FixedIndoorLocationService::FixedIndoorLocationService(const Space::LatLong& location,
                                                               const Resources::Interiors::InteriorId & interiorId,
                                                               const int floorIndex,
                                                               const double headingDegrees,
                                                               const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
        : m_location(location)
        , m_interiorId(interiorId)
        , m_floorIndex(floorIndex)
        , m_headingDegrees(headingDegrees)
        , m_environmentFlatteningService(environmentFlatteningService)
        , m_interiorInteractionModel(interiorInteractionModel)
        {
        }

        // General
        void FixedIndoorLocationService::OnPause()
        {
            
        }
        
        void FixedIndoorLocationService::OnResume()
        {
            
        }
        
        // Location
        bool FixedIndoorLocationService::IsLocationAuthorized() const
        {
            return true;
        }
        
        bool FixedIndoorLocationService::IsLocationActive() const
        {
            return true;
        }
        
        bool FixedIndoorLocationService::GetLocation(Eegeo::Space::LatLong& latlong) const
        {
            latlong.SetLatitude(m_location.GetLatitude());
            latlong.SetLongitude(m_location.GetLongitude());
            return true;
        }
        
        bool FixedIndoorLocationService::GetAltitude(double& altitude) const
        {
            const auto* pInteriorsModel = m_interiorInteractionModel.GetInteriorModel();
            
            if (pInteriorsModel == nullptr)
            {
                return false;
            }
            
            altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(
                           *pInteriorsModel, m_floorIndex, m_environmentFlatteningService.GetCurrentScale());
            return true;
        }
        
        bool FixedIndoorLocationService::GetHorizontalAccuracy(double& accuracy) const
        {
            return false;
        }
        
        void FixedIndoorLocationService::StartUpdatingLocation()
        {
            
        }
        
        void FixedIndoorLocationService::StopUpdatingLocation()
        {
            
        }
        
        // Heading
        bool FixedIndoorLocationService::GetHeadingDegrees(double& headingDegrees) const
        {
            headingDegrees = m_headingDegrees;
            return true;
        }
        
        bool FixedIndoorLocationService::IsHeadingAuthorized() const
        {
            return true;
        }
        
        bool FixedIndoorLocationService::IsHeadingActive() const
        {
            return true;
        }
        
        void FixedIndoorLocationService::StartUpdatingHeading()
        {
            
        }
        
        void FixedIndoorLocationService::StopUpdatingHeading()
        {
            
        }
        
        // Indoor
        bool FixedIndoorLocationService::IsIndoors() const
        {
            return true;
        }
        
        Resources::Interiors::InteriorId FixedIndoorLocationService::GetInteriorId() const
        {
            return Resources::Interiors::InteriorId(m_interiorId);
        }
        
        bool FixedIndoorLocationService::GetFloorIndex(int& floorIndex) const
        {
            floorIndex = m_floorIndex;
            return true;
        }
        
        bool FixedIndoorLocationService::IsIndoorAuthorized() const
        {
            return true;
        }
    }
}
