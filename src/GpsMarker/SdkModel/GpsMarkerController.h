// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGpsMarkerController.h"
#include "GpsMarker.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "Rendering.h"
#include <memory>

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerController : public IGpsMarkerController
            {
            public:
                
                GpsMarkerController(const std::shared_ptr<GpsMarkerModel>& model,
                                    const std::shared_ptr<GpsMarkerView>& view,
                                    const std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService>& environmentFlatteningService,
                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                ~GpsMarkerController();
                
                void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera);
                
            private:
                
                const static float DefaultUpdatePeriod;
                float m_updateTime;
                int m_visibilityCount;
                
                std::shared_ptr<GpsMarkerModel> m_model;
                std::shared_ptr<GpsMarkerView> m_view;
                std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService> m_environmentFlatteningService;
                std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                
                Eegeo::Helpers::TCallback1<GpsMarkerController, const Modality::ModalityChangedMessage&> m_modalityChangedHandlerBinding;
                Eegeo::Helpers::TCallback1<GpsMarkerController, const GpsMarkerVisibilityMessage&> m_visibilityChangedHandlerBinding;
                
                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);
                void OnVisbilityChangedMessage(const GpsMarkerVisibilityMessage& message);
            };
        }
    }
}