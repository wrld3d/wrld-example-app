// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGpsMarkerController.h"
#include "GpsMarker.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "IVisualMapService.h"
#include "ILocationService.h"
#include "BlueSphereView.h"
#include "BlueSphereAnchorView.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerController : public IGpsMarkerController
            {
            public:

                GpsMarkerController(GpsMarkerModel& model,
                                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                    Eegeo::Location::ILocationService& locationService,
                                    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                    VisualMap::SdkModel::IVisualMapService& visualMapService,
                                    Eegeo::BlueSphere::BlueSphereView& blueSphereView,
                                    Eegeo::BlueSphere::BlueSphereAnchorView& blueSphereAnchorView,
                                    const bool createBlueSphereViews,
                                    ExampleAppMessaging::TMessageBus& messageBus);
                ~GpsMarkerController();

                void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera);

            private:

                const static float DefaultUpdatePeriod;
                int m_visibilityCount;
                int m_currentFloorIndex;;

                GpsMarkerModel& m_model;
                Eegeo::BlueSphere::BlueSphereView& m_blueSphereView;
                Eegeo::BlueSphere::BlueSphereAnchorView& m_blueSphereAnchorView;

                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                
                VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                
                bool m_createBlueSphereViews;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback0<GpsMarkerController> m_floorSelectedCallback;
                Eegeo::Helpers::TCallback1<GpsMarkerController, const Modality::ModalityChangedMessage&> m_modalityChangedHandlerBinding;
                Eegeo::Helpers::TCallback1<GpsMarkerController, const GpsMarkerVisibilityMessage&> m_visibilityChangedHandlerBinding;
                Eegeo::Helpers::TCallback1<GpsMarkerController, const InteriorsExplorer::InteriorsExplorerStateChangedMessage&> m_interiorsExplorerStateChangedCallback;
                
                void OnFloorSelected();
                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);
                void OnVisibilityChangedMessage(const GpsMarkerVisibilityMessage& message);
                void OnInteriorsExplorerStateChangedMessage(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message);

                void GetCurrentVisualMapTime(std::string& currentTime, std::string& currentWeather);
            };
        }
    }
}
