// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerController.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerView.h"
#include "GpsMarkerAnchorView.h"
#include "VectorMath.h"
#include "EnvironmentFlatteningService.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "MathsHelpers.h"
#include "TransformHelpers.h"
#include "VisualMapState.h"
#include "ScaleHelpers.h"
#include "ScreenProperties.h"
#include "InteriorHeightHelpers.h"
#include "EarthConstants.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            const float GpsMarkerController::DefaultUpdatePeriod = 2.f;
            
            GpsMarkerController::GpsMarkerController(GpsMarkerModel& model,
                                                     GpsMarkerView& view,
                                                     GpsMarkerAnchorView& anchorView,
                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                     VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_model(model)
            , m_view(view)
            , m_anchorView(anchorView)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_visualMapService(visualMapService)
            , m_messageBus(messageBus)
            , m_visibilityCount(1)
            , m_viewTransitionParam(0)
            , m_currentFloorIndex(0)
            , m_screenPixelScale(screenProperties.GetPixelScale())
            , m_screenOversampleScale(screenProperties.GetOversampleScale())
            , m_modalityChangedHandlerBinding(this, &GpsMarkerController::OnModalityChangedMessage)
            , m_visibilityChangedHandlerBinding(this, &GpsMarkerController::OnVisibilityChangedMessage)
            , m_interiorsExplorerStateChangedCallback(this, &GpsMarkerController::OnInteriorsExplorerStateChangedMessage)
            , m_floorSelectedCallback(this, &GpsMarkerController::OnFloorSelected)
            {
                m_messageBus.SubscribeNative(m_modalityChangedHandlerBinding);
                m_messageBus.SubscribeNative(m_visibilityChangedHandlerBinding);
                m_messageBus.SubscribeUi(m_interiorsExplorerStateChangedCallback);
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_floorSelectedCallback);
                m_view.SetVisible(false);
                m_anchorView.SetVisible(false);
            }
            
            GpsMarkerController::~GpsMarkerController()
            {
                m_messageBus.UnsubscribeUi(m_interiorsExplorerStateChangedCallback);
                m_messageBus.UnsubscribeNative(m_visibilityChangedHandlerBinding);
                m_messageBus.UnsubscribeNative(m_modalityChangedHandlerBinding);
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_floorSelectedCallback);
            }
            
            void GpsMarkerController::OnFloorSelected()
            {
                m_currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
            }
            
            void GpsMarkerController::OnModalityChangedMessage(const Modality::ModalityChangedMessage &message)
            {
                float scale = 1.0f - message.Modality();
                m_view.SetScale(scale);
                m_anchorView.SetScale(scale);
            }
            
            void GpsMarkerController::OnVisibilityChangedMessage(const ExampleApp::GpsMarker::GpsMarkerVisibilityMessage &message)
            {
                m_visibilityCount += message.ShouldSetVisible() ? 1 : -1;
                Eegeo_ASSERT(m_visibilityCount <= 1, "Gps Marker sent visibility message to make visible before visibility message to be made invisible");
                m_view.SetVisible(m_visibilityCount == 1);
                m_anchorView.SetVisible(m_visibilityCount == 1);
            }
            
            void GpsMarkerController::OnInteriorsExplorerStateChangedMessage(const InteriorsExplorer::InteriorsExplorerStateChangedMessage &message)
            {
                m_currentFloorIndex = message.GetSelectedFloorIndex();
                m_view.UpdateMarkerRenderingLayer(message.IsInteriorVisible());
                m_anchorView.UpdateMarkerRenderingLayer(message.IsInteriorVisible());
            }
            
            void GpsMarkerController::Update(float dt, const Eegeo::Camera::RenderCamera &renderCamera)
            {
                m_model.UpdateGpsPosition(dt);
                m_model.UpdateHeading(dt);
                Eegeo::dv3 currentLocationEcef = m_model.GetCurrentLocationEcef();
                
                bool isVisible = false;
                if(currentLocationEcef.LengthSq() != 0 && m_visibilityCount == 1)
                {
                    if(m_model.IsLocationIndoors())
                    {
                        if(m_currentFloorIndex == m_model.GetCurrentFloorIndex())
                            isVisible = true;
                    }
                    else
                    {
                        isVisible = true;
                    }
                }
                
                m_view.SetVisible(isVisible);
                m_anchorView.SetVisible(isVisible);
                
                UpdateTransition(isVisible, dt);
                
                m_view.SetTransitionValue(m_viewTransitionParam);
                m_view.Update(dt);
                m_anchorView.SetTransitionValue(m_viewTransitionParam);
                m_anchorView.Update(dt);
                
                if(currentLocationEcef.LengthSq() == 0)
                {
                    return;
                }
                
                float currentScale = m_environmentFlatteningService.GetCurrentScale();
                if(m_model.IsLocationIndoors())
                {
                    currentScale = 1;
                }
                Eegeo::dv3 scaledPoint = m_environmentFlatteningService.GetScaledPointEcef(currentLocationEcef, currentScale);

                Eegeo::v3 markerUp = scaledPoint.Norm().ToSingle();
                
				const float scale = ExampleApp::Helpers::ScaleHelpers::ComputeModelScaleForScreenWithPixelScaling(renderCamera, scaledPoint, m_screenPixelScale, m_screenOversampleScale) * 4.25f;
                Eegeo::v3 markerScale = Eegeo::v3(scale, scale, scale);
                
                const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
                Eegeo::v3 cameraRelativeModelOrigin = (scaledPoint - ecefCameraPosition).ToSingle();
                
                Eegeo::m44 modelViewProjectionSphere;
                CreateModelViewProjectionMatrix(modelViewProjectionSphere,
                                                scaledPoint,
                                                225,
                                                cameraRelativeModelOrigin + markerUp * m_model.GetSphereHeightAboveMarker() * m_viewTransitionParam,
                                                markerScale * m_viewTransitionParam,
                                                renderCamera,
                                                true);
                Eegeo::m44 modelViewProjectionArrow;
                CreateModelViewProjectionMatrix(modelViewProjectionArrow,
                                                scaledPoint,
                                                m_model.GetSmoothedHeadingDegrees(),
                                                cameraRelativeModelOrigin + markerUp * m_model.GetSphereHeightAboveMarker() * m_viewTransitionParam,
                                                markerScale * m_viewTransitionParam,
                                                renderCamera,
                                                true);
                m_view.SetMarkerTransform(modelViewProjectionSphere, modelViewProjectionArrow);
                
                float scaleAnchor = 0.1f;
                float scaleAnchorCylinder = 0.4f;
                Eegeo::m44 modelViewProjectionAnchorSphere;
                CreateModelViewProjectionMatrix(modelViewProjectionAnchorSphere,
                                                scaledPoint,
                                                0,
                                                cameraRelativeModelOrigin + markerUp,
                                                Eegeo::v3(scaleAnchor, scaleAnchor, scaleAnchor) * m_viewTransitionParam,
                                                renderCamera,
                                                false);
                
                Eegeo::m44 modelViewProjectionAnchorCylinder;
                CreateModelViewProjectionMatrix(modelViewProjectionAnchorCylinder,
                                                scaledPoint,
                                                0,
                                                cameraRelativeModelOrigin + markerUp * m_model.GetAnchorCyclinerHeightAboveMarker(),
                                                Eegeo::v3(scaleAnchor, scaleAnchorCylinder, scaleAnchor) * m_viewTransitionParam,
                                                renderCamera,
                                                false);
                m_anchorView.SetMarkerTransform(modelViewProjectionAnchorSphere, modelViewProjectionAnchorCylinder);
                
                std::string currentTime;
                std::string currentWeather;
                GetCurrentVisualMapTime(currentTime, currentWeather);
                bool isFlattened = m_environmentFlatteningService.IsFlattened();
                m_view.SetMarkerStyle(currentTime, currentWeather, isFlattened ? m_environmentFlatteningService.GetCurrentScale() : 1);
                m_anchorView.SetMarkerStyle(currentTime, currentWeather, isFlattened ? m_environmentFlatteningService.GetCurrentScale() : 1);
            }
            
            void GpsMarkerController::UpdateTransition(bool isVisible, float dt)
            {
                if(isVisible && m_viewTransitionParam < 1.0f)
                {
                    m_viewTransitionParam += dt * 4.0f;
                }
                else if(!isVisible && m_viewTransitionParam > 0.0f)
                {
                    m_viewTransitionParam -= dt * 4.0f;
                }
                m_viewTransitionParam = Eegeo::Math::Clamp01(m_viewTransitionParam);
            }
            
            void GpsMarkerController::CreateModelViewProjectionMatrix(Eegeo::m44& out_modelViewProjection,
                                                                      const Eegeo::dv3& location,
                                                                      const float heading,
                                                                      const Eegeo::v3& cameraRelativeLocation,
                                                                      const Eegeo::v3& scale,
                                                                      const Eegeo::Camera::RenderCamera& renderCamera,
                                                                      bool flipUpDirection)
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location,
                                                                                  heading,
                                                                                  cameraInterestBasis);
                
                Eegeo::m33 basisOrientation;
                basisOrientation.SetFromBasis(-cameraInterestBasis.GetRight(), cameraInterestBasis.GetUp() * (flipUpDirection ? -1 : 1), cameraInterestBasis.GetForward());
                
                Eegeo::m44 model = Eegeo::m44::CreateScale(scale);
                Eegeo::m44::Mul(model, basisOrientation.ToM44(), model);
                model.SetRow(3, Eegeo::v4(cameraRelativeLocation, 1));
                
                Eegeo::m44 viewProjection = renderCamera.GetViewProjectionMatrix();
                
                Eegeo::m44::Mul(out_modelViewProjection, viewProjection, model);
            }
            
            void GpsMarkerController::GetCurrentVisualMapTime(std::string& currentTime, std::string& currentWeather)
            {
                const std::string& state = m_visualMapService.GetCurrentVisualMapState().GetState();
                std::string::const_reverse_iterator iter = std::find_if(state.rbegin(), state.rend(), ::isupper);
                size_t index = state.size() - std::distance(state.rbegin(), iter) - 1;
                
                currentTime = state.substr(0, index);
                currentWeather = state.substr(index);
            }
        }
    }
}
