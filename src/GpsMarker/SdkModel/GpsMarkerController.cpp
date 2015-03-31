// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerController.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerView.h"
#include "VectorMath.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            const float GpsMarkerController::DefaultUpdatePeriod = 2.f;
            
            GpsMarkerController::GpsMarkerController(GpsMarkerModel& model,
                                                     GpsMarkerView& view,
                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_model(model)
            , m_view(view)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_messageBus(messageBus)
            , m_updateTime(0.0f)
            , m_modalityChangedHandlerBinding(this, &GpsMarkerController::OnModalityChangedMessage)
            , m_visibilityChangedHandlerBinding(this, &GpsMarkerController::OnVisbilityChangedMessage)
            {
                m_messageBus.SubscribeNative(m_modalityChangedHandlerBinding);
                m_messageBus.SubscribeNative(m_visibilityChangedHandlerBinding);
                m_view.SetVisible(true);
            }
            
            GpsMarkerController::~GpsMarkerController()
            {
                m_messageBus.UnsubscribeNative(m_visibilityChangedHandlerBinding);
                m_messageBus.UnsubscribeNative(m_modalityChangedHandlerBinding);
            }
            
            void GpsMarkerController::OnModalityChangedMessage(const Modality::ModalityChangedMessage &message)
            {
                m_view.SetScale(1.0f - message.Modality());
            }
            
            void GpsMarkerController::OnVisbilityChangedMessage(const ExampleApp::GpsMarker::GpsMarkerVisibilityMessage &message)
            {
                m_view.SetVisible(message.ShouldSetVisible());
            }
            
            void GpsMarkerController::Update(float dt, const Eegeo::Camera::RenderCamera &renderCamera)
            {
                m_updateTime += dt;
                if(m_updateTime >= DefaultUpdatePeriod)
                {
                    m_model.UpdateGpsPosition();
                    m_updateTime = 0.0f;
                }
                
                m_view.Update(dt);
                
                if(m_model.HasLocation())
                {
                    m_view.DrawIconAtEcefPosition(renderCamera, m_environmentFlatteningService.GetScaledPointEcef(m_model.GetCurrentLocationEcef(), m_environmentFlatteningService.GetCurrentScale()));
                }
            }
        }
    }
}