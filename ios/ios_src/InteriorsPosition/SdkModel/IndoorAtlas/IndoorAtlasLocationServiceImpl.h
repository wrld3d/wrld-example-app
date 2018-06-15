// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Location.h"
#include "Space.h"
#include "InteriorMetaData.h"
#include "Rendering.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationServiceImpl;
            }
        }
    }
}

// class that communicates with the indoor atlas objective-c api
// try to scrape as much off this and only deal with callback passing-on
@interface IndoorAtlasLocationManager : NSObject

-(instancetype) init: (ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationServiceImpl*) indoorAtlasLocationService;

-(void) startUpdatingLocation: (NSString*) apiKey
                    apiSecret: (NSString*) apiSecret
                     floorMap: (std::map<int, std::string>) floorMap;

-(void) stopUpdatingLocation;

@end


@class IndoorAtlasLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationServiceImpl : private Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationServiceImpl(
                                                 Eegeo::Location::ILocationService& defaultLocationService,
                                                 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                                 const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                 const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                 const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
                    
                    ~IndoorAtlasLocationServiceImpl();
                    
                    // Non-interface methods
                    void SetIsAuthorized(bool isAuthorized);
                    void SetIsActive(bool isActive);
                    void SetLocation(const Eegeo::Space::LatLong &latLong);
                    void SetHorizontalAccuracy(double radius);
                    void SetFloor(const std::string& indoorAtlasFloorId, int floorIndex);

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

                    void PublishAboutPageIndoorAtlasDataMessage();
                    
                    IndoorAtlasLocationManager* m_pIndoorAtlasLocationManager;
                    Eegeo::Location::ILocationService& m_defaultLocationService;
                    const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                    const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Space::LatLong m_latLong;
                    PauseState m_pauseState;
                    std::string m_indoorAtlasFloorId;
                    int m_floorIndex;
                    double m_horizontalAccuracy;
                    bool m_isAuthorized;
                    bool m_isActive;
                };
            }
        }
    }
}

