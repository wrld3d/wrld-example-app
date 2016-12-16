// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedShowTweetState.h"
#include "IToursCameraTransitionController.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"
#include "ITourService.h"
#include "TourRepository.h"
#include "TwitterFeedPinSelectionHandler.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "EcefTangentBasis.h"
#include "CubeMapCellInfo.h"
#include "SpaceHelpers.h"
#include "WorldPinVisibility.h"
#include "WorldPinInteriorData.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorSelectionModel.h"
#include "SearchVendorNames.h"
#include "InteriorInteractionModel.h"

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
                    TwitterFeedShowTweetState::TwitterFeedShowTweetState(const TourStateModel& stateModel,
                                                                         Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                         bool isInterior,
                                                                         WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                                                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         const TweetStateData& tweetStateData,
                                                                         const Eegeo::Space::LatLong& pinLocation,
                                                                         const std::string& placeName,
                                                                         const std::string& attachedImageUrl,
                                                                         const std::string& attachedContentUrl,
                                                                         bool hasAttachedVideo,
                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                         float cameraRotationDegreesOffset)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_cameraMode(tweetStateData.ecefTarget,
                                   tweetStateData.cameraTiltDegrees,
                                   tweetStateData.cameraDistanceToTarget,
                                   cameraRotationDegreesOffset)
                    , m_pinPlacename(placeName)
                    , m_pinImageUrl(attachedImageUrl)
                    , m_pinContentUrl(attachedContentUrl)
                    , m_worldPinsService(worldPinsService)
                    , m_isInterior(isInterior)
                    , m_worldPinInteriorData(worldPinInteriorData)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorSelectionModel(interiorSelectionModel)
                    , m_pPinModel(NULL)
                    , m_cameraTransitionComplete(false)
                    , m_hasAttachedVideo(hasAttachedVideo)
                    , m_pinLocation(pinLocation)
                    , m_messageBus(messageBus)
                    {
                        float initialInterestAltitude = (float)Eegeo::Space::SpaceHelpers::GetAltitude(tweetStateData.ecefTarget);
                        
                        m_cameraMode = Camera::StaticCameraMode(m_pinLocation.ToECEF() + (initialInterestAltitude * m_pinLocation.ToECEF().Norm()),
                                                                tweetStateData.cameraTiltDegrees,
                                                                tweetStateData.cameraDistanceToTarget,
                                                                cameraRotationDegreesOffset);
                    }
                    
                    TwitterFeedShowTweetState::~TwitterFeedShowTweetState()
                    {
                        
                    }
                    
                    void TwitterFeedShowTweetState::Enter()
                    {
                        m_interiorTransitionComplete = false;
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode, true);
                        
                        if(m_isInterior && m_interiorSelectionModel.GetSelectedInteriorId() != m_worldPinInteriorData.building)
                        {
                            m_interiorSelectionModel.SelectInteriorId(m_worldPinInteriorData.building);
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        }
                        else if (!m_isInterior)
                        {
                            m_interiorSelectionModel.ClearSelection();
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        }
                    }
                    
                    void TwitterFeedShowTweetState::Update(float dt)
                    {
                        if(m_toursCameraTransitionController.IsTransitionComplete() && !m_cameraTransitionComplete)
                        {
                            m_cameraTransitionComplete = true;
                            
                            if(m_isInterior)
                            {
                                m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                            }
                            
                            rapidjson::Document jsonDocument;
                            jsonDocument.SetObject();

                            rapidjson::Document::AllocatorType& allocator = jsonDocument.GetAllocator();
                            
                            jsonDocument.AddMember("pinImageUrl", rapidjson::Value(m_pinImageUrl.c_str(), allocator).Move(), allocator);
                            jsonDocument.AddMember("pinContentUrl", rapidjson::Value(m_pinContentUrl.c_str(), allocator).Move(), allocator);
                            jsonDocument.AddMember("isVideo", m_hasAttachedVideo, allocator);
                            
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonDocument.Accept(writer);
                            
                            ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(m_pinPlacename,
                                                                                                 buffer.GetString(),
                                                                                                 Search::TourTwitterVendorName);
                            
                            Eegeo::Space::LatLong location = m_pinLocation;
                            const std::string twitterPinIconKey = "feed_twitter";
                            const float heightOffsetAboveTerrainMetres = 0.f;
                            
                            m_pPinModel = m_worldPinsService.AddPin(Eegeo_NEW(TwitterFeedPinSelectionHandler)(m_stateModel,
                                                                                                              m_messageBus),
                                                                    NULL,
                                                                    worldPinFocusData,
                                                                    m_isInterior,
                                                                    m_worldPinInteriorData,
                                                                    location,
                                                                    twitterPinIconKey,
                                                                    heightOffsetAboveTerrainMetres,
                                                                    WorldPins::SdkModel::WorldPinVisibility::TourPin);
                            // Hide hovercard if no image to show
                            if(m_pinImageUrl.empty())
                            {
                                m_pPinModel->SetFocusable(false);
                            }
                        }
                        else if(!m_interiorTransitionComplete && m_isInterior && m_interiorInteractionModel.HasInteriorModel())
                        {
                            m_interiorTransitionComplete = true;
                            m_interiorInteractionModel.SetSelectedFloorIndex(m_worldPinInteriorData.floor);
                        }
                    }
                    
                    void TwitterFeedShowTweetState::Exit()
                    {
                        if(m_pPinModel != NULL)
                        {
                            m_worldPinsService.RemovePin(m_pPinModel);
                        }
                        
                        m_pPinModel = NULL;
                    }
                }
            }
        }
    }
}