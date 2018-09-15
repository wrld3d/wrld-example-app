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
        FixedIndoorLocationService::FixedIndoorLocationService(const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
                : m_location(Eegeo::Space::LatLong(0, 0))
                , m_interiorId("")
                , m_floorIndex(0)
                , m_headingDegrees(0)
                , m_environmentFlatteningService(environmentFlatteningService)
                , m_interiorInteractionModel(interiorInteractionModel)
        {
        }

        void FixedIndoorLocationService::SetFixedLocation(const Space::LatLong& location,
                                                          const Resources::Interiors::InteriorId & interiorId,
                                                          const int floorIndex,
                                                          const double headingDegrees)
        {
            m_location = location;
            m_interiorId = interiorId;
            m_floorIndex = floorIndex;
            m_headingDegrees = headingDegrees;
        }

        Eegeo::Resources::Interiors::InteriorId FixedIndoorLocationService::GetInteriorId()
        {
            return Resources::Interiors::InteriorId(m_interiorId);
        }

        bool FixedIndoorLocationService::GetLocation(Eegeo::Space::LatLong& latlong)
        {
            latlong.SetLatitude(m_location.GetLatitude());
            latlong.SetLongitude(m_location.GetLongitude());
            return true;
        }

        bool FixedIndoorLocationService::GetAltitude(double& altitude)
        {
            const Eegeo::Resources::Interiors::InteriorsModel* pInteriorsModel = m_interiorInteractionModel.GetInteriorModel();
            if (pInteriorsModel != nullptr)
            {
                altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(*pInteriorsModel, m_floorIndex, m_environmentFlatteningService.GetCurrentScale());
                return true;
            }

            return false;
        }

        bool FixedIndoorLocationService::GetFloorIndex(int& floorIndex)
        {
            floorIndex = m_floorIndex;
            return true;
        }

        bool FixedIndoorLocationService::GetHorizontalAccuracy(double& accuracy)
        {
            return false;
        }

        bool FixedIndoorLocationService::GetHeadingDegrees(double& headingDegrees)
        {
            headingDegrees = m_headingDegrees;
            return true;
        }

        void FixedIndoorLocationService::StopListening()
        {
        }
    }
}
