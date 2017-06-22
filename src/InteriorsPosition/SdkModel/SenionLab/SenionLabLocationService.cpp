// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"
#include "InteriorHelpers.h"

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
                , m_interiorId(Eegeo::Resources::Interiors::InteriorId::NullId())
                , m_isConnected(false)
                {
                }
                
                const bool SenionLabLocationService::GetIsAuthorized() const
                {
                    if(m_isConnected)
                    {
                        return m_isAuthorized;
                    }
                    else
                    {
                        return m_defaultLocationService.GetIsAuthorized();
                    }
                }
                
                bool SenionLabLocationService::IsIndoors()
                {
                    if(m_isConnected)
                    {
                        return true;
                    }
                    else
                    {
                        return m_defaultLocationService.IsIndoors();
                    }
                }
                
                Eegeo::Resources::Interiors::InteriorId SenionLabLocationService::GetInteriorId()
                {
                    if(m_isConnected)
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel* interiorModel = m_interiorInteractionModel.GetInteriorModel();
                        if(m_interiorId.IsValid())
                        {
                            return m_interiorId;
                        }
                        else if(interiorModel != NULL)
                        {
                            return interiorModel->GetId();
                        }
                    }
                    
                    return m_defaultLocationService.GetInteriorId();
                }
                
                bool SenionLabLocationService::GetLocation(Eegeo::Space::LatLong& latLong)
                {
                    if(m_isConnected && (std::abs(m_latLong.GetLatitude()) > 0 || std::abs(m_latLong.GetLongitude()) > 0))
                    {
                        latLong.SetLatitude(m_latLong.GetLatitude());
                        latLong.SetLongitude(m_latLong.GetLongitude());
                        return true;
                    }
                    else
                    {
                        return m_defaultLocationService.GetLocation(latLong);
                    }
                }
                
                bool SenionLabLocationService::GetAltitude(double& altitude)
                {
                    if(m_isConnected)
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel* interiorModel = m_interiorInteractionModel.GetInteriorModel();
                        if(interiorModel)
                        {
                            altitude = Eegeo::Resources::Interiors::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(
                                    *interiorModel,
                                    static_cast<unsigned int>(m_floorIndex),
                                    m_environmentFlatteningService.GetCurrentScale());

                            return true;
                        }
                    
                        return false;
                    }
                    else
                    {
                        return m_defaultLocationService.GetAltitude(altitude);
                    }
                }
                
                bool SenionLabLocationService::GetFloorIndex(int& floorIndex)
                {
                    if(m_isConnected)
                    {
                        floorIndex = m_floorIndex;
                        return true;
                    }
                    else
                    {
                        return m_defaultLocationService.GetFloorIndex(floorIndex);
                    }
                }
                
                bool SenionLabLocationService::GetHorizontalAccuracy(double& accuracy)
                {
                    if(m_isConnected)
                    {
                        return false;
                    }
                    else
                    {
                        return m_defaultLocationService.GetHorizontalAccuracy(accuracy);
                    }
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
                
                void SenionLabLocationService::SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& interiorId)
                {
                    m_interiorId = interiorId;
                }
                
                void SenionLabLocationService::SetIsConnected(bool isConnected)
                {
                    m_isConnected = isConnected;
                }
            }
        }
    }
}
