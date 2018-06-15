// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#pragma once

#include "ILocationService.h"
#include "InteriorMetaData.h"
#include "Rendering.h"
#include "BidirectionalBus.h"

@class SenionLabLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationServiceImpl;

                class SenionLabLocationService : public Eegeo::Location::ILocationService, private Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationService(
                            Eegeo::Location::ILocationService& defaultLocationService,
                            ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                            const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                            const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                            const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);

                    ~SenionLabLocationService();

                    // Non-interface methods
                    void StartUpdating();
                    void StopUpdating();

                    // General
                    void OnPause() override;
                    void OnResume() override;

                    // Location
                    bool IsLocationAuthorized() const override;
                    bool IsLocationActive() const override;
                    bool GetLocation(Eegeo::Space::LatLong& latlong) const override;
                    bool GetAltitude(double& altitude) const override;
                    bool GetHorizontalAccuracy(double& accuracy) const override;

                    void StartUpdatingLocation() override;
                    void StopUpdatingLocation() override;

                    // Heading
                    bool GetHeadingDegrees(double& headingDegrees) const override;
                    bool IsHeadingAuthorized() const override;
                    bool IsHeadingActive() const override;

                    void StartUpdatingHeading() override;
                    void StopUpdatingHeading() override;

                    // Indoor
                    bool IsIndoors() const override;
                    Eegeo::Resources::Interiors::InteriorId GetInteriorId() const override;
                    bool GetFloorIndex(int& floorIndex) const override;
                    bool IsIndoorAuthorized() const override;

                private:
                    SenionLabLocationServiceImpl* m_pImpl;
                };
            }
        }
    }
}
