// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"
#include "SenionLabLocationServiceImpl.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                // public api
                SenionLabLocationService::SenionLabLocationService(
                        Eegeo::Location::ILocationService& defaultLocationService,
                        ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                        const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                        const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_pImpl(nullptr)
                {
                    m_pImpl = Eegeo_NEW(SenionLabLocationServiceImpl)(
                            defaultLocationService,
                            messageBus,
                            environmentFlatteningService,
                            interiorInteractionModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);
                }

                SenionLabLocationService::~SenionLabLocationService()
                {
                    Eegeo_DELETE(m_pImpl);
                }

                // Non-interface methods
                void SenionLabLocationService::StartUpdating()
                {
                    m_pImpl->StartUpdating();
                }

                void SenionLabLocationService::StopUpdating()
                {
                    m_pImpl->StopUpdating();
                }

                // General
                void SenionLabLocationService::OnPause()
                {
                    m_pImpl->OnPause();
                }
                
                void SenionLabLocationService::OnResume()
                {
                    m_pImpl->OnResume();
                }
                
                // Location
                bool SenionLabLocationService::IsLocationAuthorized() const
                {
                    return m_pImpl->IsLocationAuthorized();
                }
                
                bool SenionLabLocationService::IsLocationActive() const
                {
                    return m_pImpl->IsLocationActive();
                }
                
                bool SenionLabLocationService::GetLocation(Eegeo::Space::LatLong& latLong) const
                {
                    return m_pImpl->GetLocation(latLong);
                }
                
                bool SenionLabLocationService::GetAltitude(double& altitude) const
                {
                    return m_pImpl->GetAltitude(altitude);
                }
                
                bool SenionLabLocationService::GetHorizontalAccuracy(double& accuracy) const
                {
                    return m_pImpl->GetHorizontalAccuracy(accuracy);
                }
                
                void SenionLabLocationService::StartUpdatingLocation()
                {
                    m_pImpl->StartUpdatingLocation();
                }
                
                void SenionLabLocationService::StopUpdatingLocation()
                {
                    m_pImpl->StopUpdatingLocation();
                }
                
                // Heading
                bool SenionLabLocationService::GetHeadingDegrees(double& headingDegrees) const
                {
                    return m_pImpl->GetHeadingDegrees(headingDegrees);
                }
                
                bool SenionLabLocationService::IsHeadingAuthorized() const
                {
                    return m_pImpl->IsHeadingAuthorized();
                }
                
                bool SenionLabLocationService::IsHeadingActive() const
                {
                    return m_pImpl->IsHeadingActive();
                }
                
                void SenionLabLocationService::StartUpdatingHeading()
                {
                    m_pImpl->StartUpdatingHeading();
                }
                
                void SenionLabLocationService::StopUpdatingHeading()
                {
                    m_pImpl->StopUpdatingHeading();
                }
                
                // Indoor
                bool SenionLabLocationService::IsIndoors() const
                {
                    return m_pImpl->IsIndoors();
                }
                
                Eegeo::Resources::Interiors::InteriorId SenionLabLocationService::GetInteriorId() const
                {
                    return m_pImpl->GetInteriorId();
                }
                
                bool SenionLabLocationService::GetFloorIndex(int& floorIndex) const
                {
                    return m_pImpl->GetFloorIndex(floorIndex);
                }
                
                bool SenionLabLocationService::IsIndoorAuthorized() const
                {
                    return m_pImpl->IsIndoorAuthorized();
                }
            }
        }
    }
}
