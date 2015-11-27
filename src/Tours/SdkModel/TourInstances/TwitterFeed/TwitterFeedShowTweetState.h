// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourStateMachineState.h"
#include "DroneLookatCameraMode.h"
#include "Tours.h"
#include "WorldPins.h"
#include "TweetStateData.h"
#include "LatLongAltitude.h"
#include <string>

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
                    class TwitterFeedShowTweetState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                    public:
                        TwitterFeedShowTweetState(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                  ITourService& tourService,
                                                  WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                  ITourRepository& tourRepository,
                                                  const std::string& tourName,
                                                  const TweetStateData& tweetStateData,
                                                  const Eegeo::Space::LatLong& pinLocation,
                                                  const std::string& placeName,
                                                  const std::string& attachedImageUrl,
                                                  const std::string& attachedContentUrl,
                                                  bool hasAttachedVideo,
                                                  float cameraRotationOffset = 0.0f);
                        ~TwitterFeedShowTweetState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                        
                    private:
                        
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::DroneLookatCameraMode m_cameraMode;
                        ITourService& m_tourService;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        WorldPins::SdkModel::WorldPinItemModel* m_pPinModel;
                        ITourRepository& m_tourRepository;
                        const std::string m_tourName;
                        bool m_cameraTransitionComplete;
                        Eegeo::Space::LatLong m_pinLocation;
                        
                        const std::string m_pinPlacename;
                        const std::string m_pinImageUrl;
                        const std::string m_pinContentUrl;
                        const bool m_hasAttachedVideo;
                    };
                }
            }
        }
    }
}