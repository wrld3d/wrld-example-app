// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#pragma once

#include "ILocationService.h"
#include "InteriorMetaData.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "ISenionLabLocationInterop.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationService : public Eegeo::Location::ILocationService, private Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationService(ISenionLabLocationInterop& senionInterop,
                                             Eegeo::Location::ILocationService& defaultLocationService,
                                             ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                             const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                             const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);

                    ~SenionLabLocationService();

                    // Non-interface methods
                    void SetIsAuthorized(bool isAuthorized);
                    
                    void PublishAboutPageSenionDataMessage();
                    
                    void SetLocationFromSenionData(const Eegeo::Space::LatLong& latLong,
                                                   int senionFloorNumber,
                                                   int wrldFloorIndex,
                                                   double horizontalAccuracy);
                    
                    void SetHeadingFromSenionData(double headingDegrees, bool isAccurate);
                    
                    void StartUpdating();
                    void StopUpdating();
                    
                    void RestoreDefaultState();
                    
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
                    bool IsActive() const;
                    
                    struct PauseState
                    {
                        PauseState(bool paused, bool currentlyUpdatingLocation, bool currentlyUpdatingHeading)
                        : isPaused(paused)
                        , wasUpdatingLocation(currentlyUpdatingLocation)
                        , wasUpdatingHeading(currentlyUpdatingHeading)
                        {
                            
                        }
                        
                        bool isPaused;
                        bool wasUpdatingLocation;
                        bool wasUpdatingHeading;
                    };
                    
                    ISenionLabLocationInterop& m_senionInterop;
                    Eegeo::Location::ILocationService& m_defaultLocationService;
                    const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                    const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Space::LatLong m_location;
                    PauseState m_pauseState;
                    double m_horizontalAccuracy;
                    double m_headingDegrees;
                    int m_senionFloorNumber;
                    int m_wrldFloorIndex;
                    bool m_isAuthorized;
                    bool m_isLocationActive;
                    bool m_isHeadingActive;
                };
            }
        }
    }
}
