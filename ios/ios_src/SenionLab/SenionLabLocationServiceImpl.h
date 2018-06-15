// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Location.h"
#include "LatLongAltitude.h"
#include "InteriorMetaData.h"
#include "Rendering.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationServiceImpl;
            }
        }
    }
}

// class that communicates with the senion objective-c api
// try to scrape as much off this and only deal with callback passing-on
@interface SenionLabLocationManager : NSObject

-(instancetype) init: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationServiceImpl*) senionLabLocationService;

-(void) startUpdating: (NSString*) apiKey
            apiSecret: (NSString*) apiSecret
             floorMap: (std::map<int, std::string>) floorMap;

-(void) stopUpdating;

@end


@class SenionLabLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationServiceImpl : private Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationServiceImpl(
                            Eegeo::Location::ILocationService& defaultLocationService,
                            ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                            const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                            const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                            const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);

                    ~SenionLabLocationServiceImpl();

                    // Non-interface methods
                    void SetIsAuthorized(bool isAuthorized);
                    void PublishAboutPageSenionDataMessage();

                    void SetLocationFromSenionData(
                            const Eegeo::Space::LatLong& latLong,
                            int senionFloorNumber,
                            int wrldFloorIndex,
                            double horizontalAccuracy);
                    
                    void SetHeadingFromSenionData(double headingDegrees, bool isAccurate);

                    void StartUpdating();
                    void StopUpdating();

                    // General
                    void OnPause();
                    void OnResume();

                    // Location
                    bool IsLocationAuthorized() const;
                    bool IsLocationActive() const;
                    bool GetLocation(Eegeo::Space::LatLong& latlong) const;
                    bool GetAltitude(double& altitude) const;
                    bool GetHorizontalAccuracy(double& accuracy) const;

                    void StartUpdatingLocation();
                    void StopUpdatingLocation();

                    // Heading
                    bool GetHeadingDegrees(double& headingDegrees) const;
                    bool IsHeadingAuthorized() const;
                    bool IsHeadingActive() const;

                    void StartUpdatingHeading();
                    void StopUpdatingHeading();

                    // Indoor
                    bool IsIndoors() const;
                    Eegeo::Resources::Interiors::InteriorId GetInteriorId() const;
                    bool GetFloorIndex(int& floorIndex) const;
                    bool IsIndoorAuthorized() const;
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

                    struct DefaultLocationState
                    {
                        DefaultLocationState(bool currentlyUpdatingLocation, bool currentlyUpdatingHeading)
                        : wasUpdatingLocation(currentlyUpdatingLocation)
                        , wasUpdatingHeading(currentlyUpdatingHeading)
                        {
                            
                        }
                        
                        bool wasUpdatingLocation;
                        bool wasUpdatingHeading;
                    };
                    
                    SenionLabLocationManager* m_pSenionLabLocationManager;
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

