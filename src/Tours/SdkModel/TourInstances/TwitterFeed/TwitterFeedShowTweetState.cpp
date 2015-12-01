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
#include "InteriorController.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorSelectionModel.h"

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
                                                                         float cameraRotationOffset)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_cameraMode(tweetStateData.m_ecefOrigin,
                                   tweetStateData.m_ecefTarget,
                                   2.0f,
                                   cameraRotationOffset)
                    , m_pinPlacename(placeName)
                    , m_pinImageUrl(attachedImageUrl)
                    , m_pinContentUrl(attachedContentUrl)
                    , m_worldPinsService(worldPinsService)
                    , m_isInterior(isInterior)
                    , m_worldPinInteriorData(worldPinInteriorData)
                    , m_interiorController(interiorController)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_interiorSelectionModel(interiorSelectionModel)
                    , m_pPinModel(NULL)
                    , m_cameraTransitionComplete(false)
                    , m_hasAttachedVideo(hasAttachedVideo)
                    , m_pinLocation(pinLocation)
                    , m_messageBus(messageBus)
                    {
                        /* MB:  tweetStateData right now is a camera origin and camera target based on a fixed Twitter Feed position.
                                This needs to be reorientated if the location is somewhere else i.e. it's a tweet with a geolocation.  
                                Ultimately the camera should be focused on the pin location, so use that as our target and rotate the offset
                                based on a tangent basis around that point. TODO: Replace this with a better solution/better TweetStateData. */
                        
                        Eegeo::Streaming::MortonKey key = Eegeo::Space::CubeMap::EcefToKey(m_pinLocation.ToECEF(), 13);
                        Eegeo::Space::EcefTangentBasis tangentBasis = Eegeo::Space::EcefTangentBasis::CreateFromMortonKey(key);
                        float initialAltitude = (float)Eegeo::Space::SpaceHelpers::GetAltitude(tweetStateData.m_ecefOrigin);
                        float initialInterestAltitude = (float)Eegeo::Space::SpaceHelpers::GetAltitude(tweetStateData.m_ecefTarget);
                        
                        Eegeo::dv3 cameraOffset = tweetStateData.m_ecefTarget - tweetStateData.m_ecefOrigin;
                        Eegeo::m33 basis;
                        tangentBasis.GetBasisOrientationAsMatrix(basis);
                        
                        Eegeo::dv3 basisOffset = Eegeo::dv3::Mul(cameraOffset, basis);

                        m_cameraMode = Camera::DroneLookatCameraMode(m_pinLocation.ToECEF() - basisOffset + initialAltitude * tangentBasis.GetUp(),
                                                                     m_pinLocation.ToECEF() + initialInterestAltitude * tangentBasis.GetUp(),
                                                                     2.0f,
                                                                     cameraRotationOffset);
                    }
                    
                    TwitterFeedShowTweetState::~TwitterFeedShowTweetState()
                    {
                        
                    }
                    
                    void TwitterFeedShowTweetState::Enter()
                    {
                        m_interiorTransitionComplete = false;
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode);
                        
                        if(m_isInterior && m_interiorSelectionModel.GetSelectedInteriorId() != m_worldPinInteriorData.building)
                        {
                            m_interiorController.SetSelectedInterior(m_worldPinInteriorData.building);
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        }
                        else if (!m_isInterior)
                        {
                            m_interiorController.ClearSelectedInterior();
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
                            
                            jsonDocument.AddMember("pinImageUrl", m_pinImageUrl.c_str(), jsonDocument.GetAllocator());
                            jsonDocument.AddMember("pinContentUrl", m_pinContentUrl.c_str(), jsonDocument.GetAllocator());
                            jsonDocument.AddMember("isVideo", m_hasAttachedVideo, jsonDocument.GetAllocator());
                            
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonDocument.Accept(writer);
                            
                            ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(m_pinPlacename,
                                                                                                 buffer.GetString());
                            
                            Eegeo::Space::LatLong location = m_pinLocation;
                            const int BarIconIndex = 5;
                            const float heightOffsetAboveTerrainMetres = 0.f;
                            
                            m_pPinModel = m_worldPinsService.AddPin(Eegeo_NEW(TwitterFeedPinSelectionHandler)(m_stateModel,
                                                                                                              m_messageBus),
                                                                    NULL,
                                                                    worldPinFocusData,
                                                                    m_isInterior,
                                                                    m_worldPinInteriorData,
                                                                    location,
                                                                    BarIconIndex,
                                                                    heightOffsetAboveTerrainMetres,
                                                                    WorldPins::SdkModel::WorldPinVisibility::TourPin);
                        }
                        else if(!m_interiorTransitionComplete && m_isInterior && m_interiorController.InteriorInScene())
                        {
                            m_interiorTransitionComplete = true;
                            m_interiorController.SetCurrentFloor(m_worldPinInteriorData.floor);
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