// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationService.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"
#include "IndoorAtlasLocationServiceImpl.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                // public api
                IndoorAtlasLocationService::IndoorAtlasLocationService(
                        Eegeo::Location::ILocationService& defaultLocationService,
                        ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                        const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                        const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                        : m_pImpl(nullptr)
                {
                    m_pImpl = Eegeo_NEW(IndoorAtlasLocationServiceImpl)(
                            defaultLocationService,
                            messageBus,
                            environmentFlatteningService,
                            interiorInteractionModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);
                }

                IndoorAtlasLocationService::~IndoorAtlasLocationService()
                {
                    Eegeo_DELETE(m_pImpl);
                }

                // Non-interface methods
                void IndoorAtlasLocationService::StartUpdating()
                {
                    m_pImpl->StartUpdating();
                }

                void IndoorAtlasLocationService::StopUpdating()
                {
                    m_pImpl->StopUpdating();
                }

                // General
                void IndoorAtlasLocationService::OnPause()
                {
                    m_pImpl->OnPause();
                }

                void IndoorAtlasLocationService::OnResume()
                {
                    m_pImpl->OnResume();
                }

                // Location
                bool IndoorAtlasLocationService::IsLocationAuthorized() const
                {
                    return m_pImpl->IsLocationAuthorized();
                }

                bool IndoorAtlasLocationService::IsLocationActive() const
                {
                    return m_pImpl->IsLocationActive();
                }

                bool IndoorAtlasLocationService::GetLocation(Eegeo::Space::LatLong& latLong) const
                {
                    return m_pImpl->GetLocation(latLong);
                }

                bool IndoorAtlasLocationService::GetAltitude(double& altitude) const
                {
                    return m_pImpl->GetAltitude(altitude);
                }

                bool IndoorAtlasLocationService::GetHorizontalAccuracy(double& accuracy) const
                {
                    return m_pImpl->GetHorizontalAccuracy(accuracy);
                }

                void IndoorAtlasLocationService::StartUpdatingLocation()
                {
                    m_pImpl->StartUpdatingLocation();
                }

                void IndoorAtlasLocationService::StopUpdatingLocation()
                {
                    m_pImpl->StopUpdatingLocation();
                }

                // Heading
                bool IndoorAtlasLocationService::GetHeadingDegrees(double& headingDegrees) const
                {
                    return m_pImpl->GetHeadingDegrees(headingDegrees);
                }

                bool IndoorAtlasLocationService::IsHeadingAuthorized() const
                {
                    return m_pImpl->IsHeadingAuthorized();
                }

                bool IndoorAtlasLocationService::IsHeadingActive() const
                {
                    return m_pImpl->IsHeadingActive();
                }

                void IndoorAtlasLocationService::StartUpdatingHeading()
                {
                    m_pImpl->StartUpdatingHeading();
                }

                void IndoorAtlasLocationService::StopUpdatingHeading()
                {
                    m_pImpl->StopUpdatingHeading();
                }

                // Indoor
                bool IndoorAtlasLocationService::IsIndoors() const
                {
                    return m_pImpl->IsIndoors();
                }

                Eegeo::Resources::Interiors::InteriorId IndoorAtlasLocationService::GetInteriorId() const
                {
                    return m_pImpl->GetInteriorId();
                }

                bool IndoorAtlasLocationService::GetFloorIndex(int& floorIndex) const
                {
                    return m_pImpl->GetFloorIndex(floorIndex);
                }

                bool IndoorAtlasLocationService::IsIndoorAuthorized() const
                {
                    return m_pImpl->IsIndoorAuthorized();
                }
            }
        }
    }
}
