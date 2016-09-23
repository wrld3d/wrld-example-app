// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerController.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerView.h"
#include "VectorMath.h"
#include "EnvironmentFlatteningService.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "MathsHelpers.h"
#include "TransformHelpers.h"
#include "VisualMapState.h"

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
                                                     VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_model(model)
            , m_view(view)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_visualMapService(visualMapService)
            , m_messageBus(messageBus)
            , m_updateTime(0.0f)
            , m_visibilityCount(1)
            , m_modalityChangedHandlerBinding(this, &GpsMarkerController::OnModalityChangedMessage)
            , m_visibilityChangedHandlerBinding(this, &GpsMarkerController::OnVisbilityChangedMessage)
            , m_interiorsExplorerStateChangedCallback(this, &GpsMarkerController::OnInteriorsExplorerStateChangedMessage)
            {
                m_messageBus.SubscribeNative(m_modalityChangedHandlerBinding);
                m_messageBus.SubscribeNative(m_visibilityChangedHandlerBinding);
                m_messageBus.SubscribeUi(m_interiorsExplorerStateChangedCallback);
                m_view.SetVisible(true);
            }
            
            GpsMarkerController::~GpsMarkerController()
            {
                m_messageBus.UnsubscribeUi(m_interiorsExplorerStateChangedCallback);
                m_messageBus.UnsubscribeNative(m_visibilityChangedHandlerBinding);
                m_messageBus.UnsubscribeNative(m_modalityChangedHandlerBinding);
            }
            
            void GpsMarkerController::OnModalityChangedMessage(const Modality::ModalityChangedMessage &message)
            {
                m_view.SetScale(1.0f - message.Modality());
            }
            
            void GpsMarkerController::OnVisbilityChangedMessage(const ExampleApp::GpsMarker::GpsMarkerVisibilityMessage &message)
            {
                m_visibilityCount += message.ShouldSetVisible() ? 1 : -1;
                Eegeo_ASSERT(m_visibilityCount <= 1, "Gps Marker sent visibility message to make visible before visibility message to be made invisible");
                m_view.SetVisible(m_visibilityCount == 1);
            }
            
            void GpsMarkerController::OnInteriorsExplorerStateChangedMessage(const InteriorsExplorer::InteriorsExplorerStateChangedMessage &message)
            {
                m_view.UpdateMarkerRenderingLayer(message.IsInteriorVisible());
            }
            
            void GpsMarkerController::Update(float dt, const Eegeo::Camera::RenderCamera &renderCamera)
            {
                m_updateTime += dt;
                if(m_updateTime >= DefaultUpdatePeriod)
                {
                    m_model.UpdateGpsPosition();
                    m_updateTime = 0.0f;
                }
                
                m_model.UpdateHeading(dt);
                m_view.Update(dt);
                
                Eegeo::dv3 currentLocationEcef = m_model.GetCurrentLocationEcef();
                Eegeo::dv3 scaledPoint = m_environmentFlatteningService.GetScaledPointEcef(currentLocationEcef, m_environmentFlatteningService.GetCurrentScale());
                
                if(currentLocationEcef.LengthSq() == 0)
                {
                    return;
                }
                
                float scale = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(renderCamera, scaledPoint) * 0.025f;
                Eegeo::m44 transformMatrix = Eegeo::m44::CreateIdentity();
                transformMatrix.Scale(scale);
                
                const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
                Eegeo::v3 cameraRelativeModelOrigin = (scaledPoint - ecefCameraPosition).ToSingle();
                transformMatrix.SetRow(3, Eegeo::v4(cameraRelativeModelOrigin, 1) + Eegeo::v4(scaledPoint.Norm().ToSingle() * 5, 0));
                
                Eegeo::m44 modelViewProjection;
                CreateModelViewProjectionMatrix(modelViewProjection, scaledPoint, 225, transformMatrix, renderCamera);
                Eegeo::m44 modelViewProjectionArrow;
                CreateModelViewProjectionMatrix(modelViewProjectionArrow, scaledPoint, m_model.GetSmoothedHeadingDegrees(), transformMatrix, renderCamera);
                m_view.SetMarkerTransform(modelViewProjection, modelViewProjectionArrow);
                
                const std::string currentTime = GetCurrentVisualMapTime();
                m_view.SetMarkerStyle(currentTime);
            }
            
            void GpsMarkerController::CreateModelViewProjectionMatrix(Eegeo::m44& out_modelViewProjection,
                                                                      const Eegeo::dv3& location,
                                                                      const float heading,
                                                                      const Eegeo::m44& transformMatrix,
                                                                      const Eegeo::Camera::RenderCamera& renderCamera)
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location,
                                                                                  heading,
                                                                                  cameraInterestBasis);
                
                Eegeo::m33 basisOrientation;
                basisOrientation.SetFromBasis(-cameraInterestBasis.GetRight(), -cameraInterestBasis.GetUp(), cameraInterestBasis.GetForward());
                
                Eegeo::m44 model;
                Eegeo::m44::Mul(model, transformMatrix, basisOrientation.ToM44());
                
                Eegeo::m44 viewProjection = renderCamera.GetViewProjectionMatrix();
                
                Eegeo::m44::Mul(out_modelViewProjection, viewProjection, model);
            }
            
            const std::string GpsMarkerController::GetCurrentVisualMapTime()
            {
                const std::string& state = m_visualMapService.GetCurrentVisualMapState().GetState();
                std::string::const_reverse_iterator iter = std::find_if(state.rbegin(), state.rend(), ::isupper);
                size_t index = state.size() - std::distance(state.rbegin(), iter) - 1;
                
                const std::string time = state.substr(0, index);
                return time;
            }
        }
    }
}