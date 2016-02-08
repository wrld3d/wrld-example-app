// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedTourModule.h"
#include "TwitterFeedTourObserver.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    TwitterFeedTourModule::TwitterFeedTourModule(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                 ITourService& tourService,
                                                                 WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                 Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                 InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 ITourRepository& tourRepository,
                                                                 Social::TwitterFeed::ITwitterFeedService& twitterFeedService,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                    {
                        std::map<std::string, int> twitterTourIconOverrideMap;

                        const bool isInterior = false;
                        const WorldPins::SdkModel::WorldPinInteriorData noInteirorData;
                        const bool useBounds = false;
                        
                        const float externalCameraDistance = 600.0f;
                        const float externalCameraTiltDegrees = 45.0f;
                        m_tweetStateDataMap["Dev4Recce"] = TweetStateData(Eegeo::Space::LatLongAltitude::FromDegrees(37.617398, -122.376256, 100).ToECEF(),
                                                                          externalCameraDistance,
                                                                          externalCameraTiltDegrees,
                                                                          true,
                                                                          isInterior,
                                                                          noInteirorData,
                                                                          useBounds,
                                                                          Eegeo::Space::LatLong(0,0),
                                                                          Eegeo::Space::LatLong(0,0));
                        
                        m_pTwitterFeedTourObserver = Eegeo_NEW(TwitterFeedTourObserver)(toursCameraTransitionController,
                                                                                        tourService,
                                                                                        worldPinsService,
                                                                                        interiorController,
                                                                                        interiorVisibilityUpdater,
                                                                                        interiorSelectionModel,
                                                                                        tourRepository,
                                                                                        twitterFeedService,
                                                                                        m_tweetStateDataMap,
                                                                                        twitterTourIconOverrideMap,
                                                                                        messageBus);
                    }
                    
                    TwitterFeedTourModule::~TwitterFeedTourModule()
                    {
                        Eegeo_DELETE m_pTwitterFeedTourObserver;
                        
                        m_tweetStateDataMap.clear();
                    }
                    
                    const std::map<std::string, TweetStateData>& TwitterFeedTourModule::GetTweetStateDataMap() const
                    {
                        return m_tweetStateDataMap;
                    }
                }
            }
        }
    }
}