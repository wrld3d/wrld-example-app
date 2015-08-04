// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "GlobeCamera.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsControllerExitObserver
        {
        public:
            InteriorsControllerExitObserver(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                            Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController);

            ~InteriorsControllerExitObserver();

        private:
            void OnInteriorsControllerExit();

            Eegeo::Resources::Interiors::InteriorsController& m_interiorsController;
            Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;

            Eegeo::Helpers::TCallback0<InteriorsControllerExitObserver> m_onInteriorsControllerExitCallback;
        };
    }
}