// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsInFocusController.h"

#include <limits>

#include "IWorldPinsService.h"
#include "VectorMath.h"
#include "IInterestPointProvider.h"
#include "RenderCamera.h"
#include "IWorldPinsRepository.h"
#include "WorldPinsInFocusModel.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"
#include "Logger.h"

namespace ExampleApp
{
	namespace WorldPins
	{
        WorldPinsInFocusController::WorldPinsInFocusController(IWorldPinsRepository& worldPinsRepository,
                                                               IWorldPinsService& worldPinsService,
                                                               ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_worldPinsRepository(worldPinsRepository)
        , m_worldPinsService(worldPinsService)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_pLastFocussedModel(NULL)
		{

		}

		WorldPinsInFocusController::~WorldPinsInFocusController()
		{

		}

        void WorldPinsInFocusController::Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera)
		{
			const IWorldPinsInFocusModel* pClosest = NULL;
			double minDistanceSq = std::numeric_limits<double>::max();
			Eegeo::v2 closestScreenPinLocation;
            
            for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
			{
                ExampleApp::WorldPins::WorldPinItemModel* worldPinItemModel = m_worldPinsRepository.GetItemAtIndex(i);

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
				
				Eegeo::v3 screenPos;
				renderCamera.Project(cameraLocal, screenPos);
				screenPinLocation.Set(screenPos.GetX(), screenPos.GetY());

				double distanceToFocusSq = (ecefInterestPoint - ecefPinLocation).LengthSq();

				if(distanceToFocusSq < minDistanceSq && worldPinItemModel->IsVisible())
				{
                    pClosest = &worldPinItemModel->GetInFocusModel();
					minDistanceSq = distanceToFocusSq;
					closestScreenPinLocation = screenPinLocation;
				}
			}

			if(m_pLastFocussedModel != pClosest)
			{
				m_pLastFocussedModel = pClosest;

				if(m_pLastFocussedModel != NULL)
				{
					m_nativeToUiMessageBus.Publish(WorldPinGainedFocusMessage(WorldPinsInFocusModel(m_pLastFocussedModel->GetPinId(),
                                                                                                    m_pLastFocussedModel->GetTitle(),
                                                                                                    m_pLastFocussedModel->GetSubtitle()),
                                                                              closestScreenPinLocation));
				}
				else
				{
					m_nativeToUiMessageBus.Publish(WorldPinLostFocusMessage());
				}
			}
			else
			{
				if(m_pLastFocussedModel != NULL)
				{
					m_nativeToUiMessageBus.Publish(WorldPinInFocusChangedLocationMessage(closestScreenPinLocation));
				}
			}
		}
	}
}
