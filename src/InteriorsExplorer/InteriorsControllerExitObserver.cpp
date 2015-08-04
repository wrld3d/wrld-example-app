// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsControllerExitObserver.h"
#include "InteriorsController.h"
#include "InteriorsCameraController.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        InteriorsControllerExitObserver::InteriorsControllerExitObserver(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                                         Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController)
        : m_interiorsController(interiorsController)
        , m_globeCameraController(globeCameraController)
        , m_onInteriorsControllerExitCallback(this, &InteriorsControllerExitObserver::OnInteriorsControllerExit)
        {
            m_interiorsController.RegisterExitCallback(m_onInteriorsControllerExitCallback);
        }

        InteriorsControllerExitObserver::~InteriorsControllerExitObserver()
        {
            m_interiorsController.UnregisterExitCallback(m_onInteriorsControllerExitCallback);
        }

        void InteriorsControllerExitObserver::OnInteriorsControllerExit()
        {
            const Eegeo::Resources::Interiors::Camera::InteriorsCameraState& defaultExitTransitionTarget = m_interiorsController.GetExitTransitionTarget();

            Eegeo::v3 camToInterest = (defaultExitTransitionTarget.GetInterestPointEcef() - defaultExitTransitionTarget.GetLocationEcef()).ToSingle();
            const Eegeo::v3& camDir = camToInterest.Norm();

            Eegeo::Space::EcefTangentBasis interestBasis(defaultExitTransitionTarget.GetInterestPointEcef(), camDir);

            float currentCameraDist = camToInterest.Length();

            m_globeCameraController.SetView(interestBasis, currentCameraDist);

            const Eegeo::Resources::Interiors::Camera::InteriorsCameraState& exitTransitionTarget = Eegeo::Resources::Interiors::Camera::InteriorsCameraState::MakeFromRenderCamera(m_globeCameraController.GetRenderCamera());

            m_interiorsController.SetExitTransitionTarget(exitTransitionTarget);
        }
    }
}