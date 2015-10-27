// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsInFocusController.h"

#include <limits>

#include "CameraHelpers.h"
#include "IWorldPinsService.h"
#include "VectorMath.h"
#include "IInterestPointProvider.h"
#include "RenderCamera.h"
#include "IWorldPinsRepository.h"
#include "WorldPinsInFocusModel.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"
#include "WorldPinsVisibilityMessage.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace
            {
                Eegeo::v2 ProjectEcefToScreen(const Eegeo::dv3& ecefPoint, const Eegeo::Camera::RenderCamera& renderCamera)
                {
                    Eegeo::v3 cameraLocal = Eegeo::Camera::CameraHelpers::CameraRelativePoint(ecefPoint, renderCamera.GetEcefLocation());
                    Eegeo::v3 screenPos;
                    renderCamera.Project(cameraLocal, screenPos);
                    return Eegeo::v2(screenPos.GetX(), screenPos.GetY());
                }
            }
            
            WorldPinsInFocusController::WorldPinsInFocusController(IWorldPinsRepository& worldPinsRepository,
                    IWorldPinsService& worldPinsService,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_worldPinsRepository(worldPinsRepository)
                , m_worldPinsService(worldPinsService)
                , m_messageBus(messageBus)
                , m_visibilityMessageHandlerBinding(this, &WorldPinsInFocusController::OnWorldPinsVisibilityMessage)
                , m_pLastFocussedModel(NULL)
                , m_focusEnabled(true)
            {
                m_messageBus.SubscribeNative(m_visibilityMessageHandlerBinding);
            }

            WorldPinsInFocusController::~WorldPinsInFocusController()
            {
                m_messageBus.UnsubscribeNative(m_visibilityMessageHandlerBinding);
            }

            void WorldPinsInFocusController::Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera)
            {
                const IWorldPinsInFocusModel* pClosest = NULL;
                double minDistanceSq = std::numeric_limits<double>::max();
                Eegeo::v2 closestScreenPinLocation;
                Eegeo::v2 screenInterestPoint = ProjectEcefToScreen(ecefInterestPoint, renderCamera);

                if(m_focusEnabled)
                {
                    for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                    {
                        ExampleApp::WorldPins::SdkModel::WorldPinItemModel* worldPinItemModel = m_worldPinsRepository.GetItemAtIndex(i);

                        if (!worldPinItemModel->IsFocusable())
                        {
                            continue;
                        }
                        
                        Eegeo::dv3 ecefPinLocation;
                        Eegeo::v2 screenPinLocation;

                        m_worldPinsService.GetPinEcefAndScreenLocations(*worldPinItemModel,
                                ecefPinLocation,
                                screenPinLocation);

                        Eegeo::v3 cameraLocal = (ecefPinLocation - renderCamera.GetEcefLocation()).ToSingle();
                        Eegeo::v3 cameraSurfaceNormal = cameraLocal.Norm();

                        Eegeo::v3 upNormal = ecefPinLocation.Norm().ToSingle();
                        float dp = Eegeo::v3::Dot(cameraSurfaceNormal, upNormal);

                        if(dp > 0.0f)
                        {
                            continue;
                        }

                        screenPinLocation = ProjectEcefToScreen(ecefPinLocation, renderCamera);

                        double distanceToFocusSq = (screenInterestPoint - screenPinLocation).LengthSq();

                        if(distanceToFocusSq < minDistanceSq && worldPinItemModel->IsVisible())
                        {
                            pClosest = &worldPinItemModel->GetInFocusModel();
                            minDistanceSq = distanceToFocusSq;
                            closestScreenPinLocation = screenPinLocation;
                        }
                    }
                }

                if(m_pLastFocussedModel != pClosest)
                {
                    m_pLastFocussedModel = pClosest;

                    if(m_pLastFocussedModel != NULL)
                    {
                        m_messageBus.Publish(WorldPinGainedFocusMessage(WorldPinsInFocusModel(m_pLastFocussedModel->GetPinId(),
                                             m_pLastFocussedModel->GetTitle(),
                                             m_pLastFocussedModel->GetSubtitle(),
                                             m_pLastFocussedModel->GetRatingsImage(),
                                             m_pLastFocussedModel->GetReviewCount()),
                                             closestScreenPinLocation));
                    }
                    else
                    {
                        m_messageBus.Publish(WorldPinLostFocusMessage());
                    }
                }
                else
                {
                    if(m_pLastFocussedModel != NULL)
                    {
                        m_messageBus.Publish(WorldPinInFocusChangedLocationMessage(closestScreenPinLocation));
                    }
                }
            }

            void WorldPinsInFocusController::OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage &worldPinsVisibilityMessage)
            {
                m_focusEnabled = worldPinsVisibilityMessage.ShouldSetVisible();
            }
        }
    }
}
