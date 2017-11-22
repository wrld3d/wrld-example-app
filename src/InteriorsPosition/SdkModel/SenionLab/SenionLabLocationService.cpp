// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"
#include "InteriorHelpers.h"
#include "InteriorsPositionConnectionMessage.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace
            {
                float timeBeforeDisconnect = 30.0f;
            }
            
            namespace SenionLab
            {   
                SenionLabLocationService::SenionLabLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                                                   const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                   const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
                : m_defaultLocationService(defaultLocationService)
                , m_environmentFlatteningService(environmentFlatteningService)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_isAuthorized(false)
                , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
                , m_floorIndex(-1)
                , m_interiorId(Eegeo::Resources::Interiors::InteriorId::NullId())
                , m_isConnected(false)
                , m_headingDegrees(0.0)
                , m_disconnectTime(0.0f)
                , m_messageBus(messageBus)
                {
                }
                
                const bool SenionLabLocationService::GetIsAuthorized() const
                {
                    if(ShouldUseSenionData())
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
                    if(ShouldUseSenionData())
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
                    if(ShouldUseSenionData())
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
                    if(ShouldUseSenionData() && (std::abs(m_latLong.GetLatitude()) > 0 || std::abs(m_latLong.GetLongitude()) > 0))
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
                    if(ShouldUseSenionData())
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
                    if(ShouldUseSenionData())
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
                    if(ShouldUseSenionData())
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
                    if (ShouldUseSenionData())
                    {
                        headingDegrees = m_headingDegrees;
                        return true;
                    }
                    
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
                
                void SenionLabLocationService::SetHeadingDegrees(double headingDegrees)
                {
                    m_headingDegrees = headingDegrees;
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
                    if(m_isConnected != isConnected)
                    {
                        InteriorsPositionConnectionMessage message(isConnected);
                        m_messageBus.Publish(message);
                    }
                    
                    m_isConnected = isConnected;
                    
                    if(m_isConnected)
                    {
                        m_disconnectTime = 0.0f;
                    }
                }
                
                void SenionLabLocationService::Update(float dt)
                {
                    if(!m_isConnected && m_disconnectTime < timeBeforeDisconnect)
                    {
                        m_disconnectTime += dt;
                    }
                }
                
                bool SenionLabLocationService::ShouldUseSenionData() const
                {
                    if(m_isConnected || m_disconnectTime < timeBeforeDisconnect)
                    {
                        return true;
                    }
                    
                    return false;
                }
            }
        }
    }
}
