// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerController.h"
#include "GpsMarkerModel.h"
#include "EnvironmentFlatteningService.h"
#include "CameraHelpers.h"
#include "VisualMapState.h"
#include "ScreenProperties.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "BlueSphereConfiguration.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            const float GpsMarkerController::DefaultUpdatePeriod = 2.f;

            GpsMarkerController::GpsMarkerController(GpsMarkerModel& model,
                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Location::ILocationService& locationService,
                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                     VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                     Eegeo::BlueSphere::BlueSphereView& blueSphereView,
                                                     Eegeo::BlueSphere::BlueSphereAnchorView& blueSphereAnchorView,
                                                     const bool createBlueSphereViews,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_model(model)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_visualMapService(visualMapService)
            , m_messageBus(messageBus)
            , m_visibilityCount(1)
            , m_currentFloorIndex(0)
            , m_modalityChangedHandlerBinding(this, &GpsMarkerController::OnModalityChangedMessage)
            , m_visibilityChangedHandlerBinding(this, &GpsMarkerController::OnVisibilityChangedMessage)
            , m_interiorsExplorerStateChangedCallback(this, &GpsMarkerController::OnInteriorsExplorerStateChangedMessage)
            , m_floorSelectedCallback(this, &GpsMarkerController::OnFloorSelected)
            , m_blueSphereView(blueSphereView)
            , m_blueSphereAnchorView(blueSphereAnchorView)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_createBlueSphereViews(createBlueSphereViews)
            {
                
                if(m_createBlueSphereViews)
                {
                    m_messageBus.SubscribeNative(m_modalityChangedHandlerBinding);
                    m_messageBus.SubscribeNative(m_visibilityChangedHandlerBinding);
                    m_messageBus.SubscribeUi(m_interiorsExplorerStateChangedCallback);
                }
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_floorSelectedCallback);
            }

            GpsMarkerController::~GpsMarkerController()
            {
                if(m_createBlueSphereViews)
                {
                    m_messageBus.UnsubscribeUi(m_interiorsExplorerStateChangedCallback);
                    m_messageBus.UnsubscribeNative(m_visibilityChangedHandlerBinding);
                    m_messageBus.UnsubscribeNative(m_modalityChangedHandlerBinding);
                }
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_floorSelectedCallback);
            }

            void GpsMarkerController::OnFloorSelected()
            {
                m_currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
            }

            void GpsMarkerController::OnModalityChangedMessage(const Modality::ModalityChangedMessage &message)
            {
                float scale = 1.0f - message.Modality();
                m_blueSphereView.SetScale(scale);
                m_blueSphereAnchorView.SetScale(scale);
            }

            void GpsMarkerController::OnVisibilityChangedMessage(const ExampleApp::GpsMarker::GpsMarkerVisibilityMessage &message)
            {
                m_visibilityCount += message.ShouldSetVisible() ? 1 : -1;
                Eegeo_ASSERT(m_visibilityCount <= 1, "Gps Marker sent visibility message to make visible before visibility message to be made invisible");
                m_blueSphereView.SetVisible(m_visibilityCount == 1);
                m_blueSphereAnchorView.SetVisible(m_visibilityCount == 1);
            }

            void GpsMarkerController::OnInteriorsExplorerStateChangedMessage(const InteriorsExplorer::InteriorsExplorerStateChangedMessage &message)
            {
                m_currentFloorIndex = message.GetSelectedFloorIndex();
                m_blueSphereView.UpdateBlueSphereRenderingLayer(message.IsInteriorVisible());
                m_blueSphereAnchorView.UpdateBlueSphereRenderingLayer(message.IsInteriorVisible());
            }

            void GpsMarkerController::Update(float dt, const Eegeo::Camera::RenderCamera &renderCamera)
            {
                bool positionValid = m_model.UpdateGpsPosition(dt);
                m_model.UpdateHeading(dt);

                m_model.SetEnabled(m_visibilityCount == 1 && positionValid);

                std::string currentTime;
                std::string currentWeather;
                GetCurrentVisualMapTime(currentTime, currentWeather);
                bool isFlattened = m_environmentFlatteningService.IsFlattened();
               if(m_createBlueSphereViews)
                {
                    m_blueSphereView.SetBlueSphereStyle(currentTime, currentWeather, isFlattened ? m_environmentFlatteningService.GetCurrentScale() : 1);
                    m_blueSphereAnchorView.SetBlueSphereStyle(currentTime, currentWeather, isFlattened ? m_environmentFlatteningService.GetCurrentScale() : 1);
                }
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
