// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "InteriorHeightHelpers.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationService::SenionLabLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                                                   const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                   const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
                : m_defaultLocationService(defaultLocationService)
                , m_environmentFlatteningService(environmentFlatteningService)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_isAuthorized(false)
                , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
                , m_floorIndex(-1)
                {
                }
                
                const bool SenionLabLocationService::GetIsAuthorized() const
                {
                    return m_isAuthorized;
                }
                
                bool SenionLabLocationService::IsIndoors()
                {
                    return true;
                }
                
                Eegeo::Resources::Interiors::InteriorId SenionLabLocationService::GetInteriorId()
                {
                    if(m_interiorInteractionModel.HasInteriorModel())
                    {
                        return m_interiorInteractionModel.GetInteriorModel()->GetId();
                    }
                    else return Eegeo::Resources::Interiors::InteriorId::NullId();
                }
                
                bool SenionLabLocationService::GetLocation(Eegeo::Space::LatLong& latLong)
                {
                    latLong.SetLatitude(m_latLong.GetLatitude());
                    latLong.SetLongitude(m_latLong.GetLongitude());
                    return true;
                }
                
                bool SenionLabLocationService::GetAltitude(double& altitude)
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
                
                bool SenionLabLocationService::GetFloorIndex(int& floorIndex)
                {
                    floorIndex = m_floorIndex;
                    return true;
                }
                
                bool SenionLabLocationService::GetHorizontalAccuracy(double& accuracy)
                {
                    return false;
                }
                
                bool SenionLabLocationService::GetHeadingDegrees(double& headingDegrees)
                {
                    return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
                }
                
                void SenionLabLocationService::StopListening()
                {
                }
                
                void SenionLabLocationService::SetIsAuthorized(bool isAuthorized)
                {
                    m_isAuthorized = isAuthorized;
                }
                
                void SenionLabLocationService::SetLocation(Eegeo::Space::LatLong &latLong)
                {
                    m_latLong = latLong;
                }
                
                void SenionLabLocationService::SetFloorIndex(int floorIndex)
                {
                    m_floorIndex = floorIndex;
                }
            }
        }
    }
}
