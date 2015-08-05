// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <InteriorsPinsController.h>
#include "InteriorsExplorerInputDelegate.h"
#include "InteriorsController.h"
#include "GpsGlobeCameraController.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerInputDelegate::InteriorsExplorerInputDelegate(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                                           Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                                           Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController)
            : m_interiorsController(interiorsController)
            , m_interiorsPinsController(interiorsPinsController)
            , m_globeCameraController(globeCameraController)
            {

            }

            bool InteriorsExplorerInputDelegate::HandleTouchTap(const AppInterface::TapData& tapData)
            {
                Eegeo::Resources::Interiors::InteriorId selectedInteriorId;
                if (m_interiorsPinsController.Event_TouchTap(tapData, selectedInteriorId))
                {
                    const Eegeo::Resources::Interiors::Camera::InteriorsCameraState& initialInteriorsCameraState = Eegeo::Resources::Interiors::Camera::InteriorsCameraState::MakeFromRenderCamera(m_globeCameraController.GetRenderCamera());

                    bool success = m_interiorsController.TryEnterInterior(selectedInteriorId, initialInteriorsCameraState);
                    return success;
                }

                return false;
            }
        }
    }
}