// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchTransitionPinSelectionHandler.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchTransitionPinSelectionHandler::SwallowSearchTransitionPinSelectionHandler(const SwallowTransitionResultModel& transitionResult,
                                                                                                       CameraTransitions::SdkModel::ICameraTransitionController& transitionController)
                : m_transitionResult(transitionResult)
                , m_transitionController(transitionController)
                {
                    
                }
                
                void SwallowSearchTransitionPinSelectionHandler::SelectPin()
                {
                    m_transitionController.StartTransitionTo(m_transitionResult.GetTargetLatLong().ToECEF(), InteriorsExplorer::DefaultInteriorTransitionInterestDistance,  m_transitionResult.GetTargetInteriorId(), m_transitionResult.GetTargetInteriorFloor());
                }
            }
        }
    }
}