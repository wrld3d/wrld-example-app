// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <InteriorsController.h>
#include <GpsGlobeCameraController.h>
#include "EegeoUI.h"
#include "Interiors.h"
#include "GlobeCamera.h"
#include "ICallback.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "ISingleOptionAlertBox.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExitObserver : public Eegeo::UI::NativeAlerts::ISingleOptionAlertBoxDismissedHandler
        {
        public:
            InteriorsExitObserver(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                  Eegeo::Resources::Interiors::InteriorSelectionController& interiorSelectionController,
                                  Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                  Eegeo::UI::NativeUIFactories& nativeUiFactories);

            ~InteriorsExitObserver();

        private:
            Eegeo::Resources::Interiors::InteriorsController& m_interiorsController;
            Eegeo::Resources::Interiors::InteriorSelectionController& m_interiorSelectionController;
            Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;
            Eegeo::UI::NativeUIFactories& m_nativeUiFactories;
            Eegeo::UI::NativeAlerts::ISingleOptionAlertBox* m_pAlertBox;

            Eegeo::Helpers::TCallback0<InteriorsExitObserver> m_onInteriorsControllerExitCallback;
            void OnInteriorsControllerExit();

            Eegeo::Helpers::TCallback0<InteriorsExitObserver> m_failedToStreamResourceCallback;
            void OnFailedToStreamResource();

            void HandleAlertBoxDismissed();

            void InitialiseTransitionToGlobeCamera(float additionalDistanceOffset);
        };
    }
}