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
#include "TourStateModel.h"
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"

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
                        TwitterFeedShowTweetState(const TourStateModel& stateModel,
                                                  Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                  WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                  bool isInterior,
                                                  WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                                                  Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                  InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                  const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                  const TweetStateData& tweetStateData,
                                                  const Eegeo::Space::LatLong& pinLocation,
                                                  const std::string& placeName,
                                                  const std::string& attachedImageUrl,
                                                  const std::string& attachedContentUrl,
                                                  bool hasAttachedVideo,
                                                  ExampleAppMessaging::TMessageBus& messageBus,
                                                  float cameraRotationOffset = 0.0f);
                        ~TwitterFeedShowTweetState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                        
                    private:
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::DroneLookatCameraMode m_cameraMode;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        WorldPins::SdkModel::WorldPinItemModel* m_pPinModel;
                        bool m_cameraTransitionComplete;
                        bool m_interiorTransitionComplete;
                        Eegeo::Space::LatLong m_pinLocation;
                        bool m_isInterior;
                        WorldPins::SdkModel::WorldPinInteriorData m_worldPinInteriorData;
                        Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        
                        const std::string m_pinPlacename;
                        const std::string m_pinImageUrl;
                        const std::string m_pinContentUrl;
                        const bool m_hasAttachedVideo;
                        
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                    };
                }
            }
        }
    }
}