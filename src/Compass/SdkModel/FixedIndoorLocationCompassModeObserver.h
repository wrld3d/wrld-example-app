// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "CompassModeObserver.h"
#include "ICompassModel.h"
#include "ICallback.h"
#include "CameraTransitionService.h"
#include "VectorMath.h"
#include "ApplicationFixedIndoorLocation.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class FixedIndoorLocationCompassModeObserver : public CompassModeObserver
            {
            private:
                CameraTransitions::SdkModel::CameraTransitionService& m_cameraTransitionService;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                Eegeo::dv3 m_location;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_floorIndex;
                double m_fixedHeadingRadians;

            protected:
                void OnGpsModeChanged();

            public:
                FixedIndoorLocationCompassModeObserver(
                    ICompassModel& model,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService,
                    Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                    const ApplicationConfig::SdkModel::ApplicationFixedIndoorLocation& fixedIndoorLocation);
            };
        }
    }
}
