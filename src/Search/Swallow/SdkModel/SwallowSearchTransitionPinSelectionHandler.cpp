// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchTransitionPinSelectionHandler.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchTransitionPinSelectionHandler::SwallowSearchTransitionPinSelectionHandler(const SwallowTransitionResultModel& transitionResult)
                : m_transitionResult(transitionResult)
                {
                    
                }
                
                void SwallowSearchTransitionPinSelectionHandler::SelectPin()
                {
                    // TODO: jump to interior specified in transition result
                    Eegeo_TTY("TRANSITION TO %s, FLOOR %d", m_transitionResult.GetTargetInteriorId().Value().c_str(), m_transitionResult.GetTargetInteriorFloor());
                }
            }
        }
    }
}