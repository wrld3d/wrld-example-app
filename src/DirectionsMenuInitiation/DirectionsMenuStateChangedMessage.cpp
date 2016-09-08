// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        DirectionsMenuStateChangedMessage::DirectionsMenuStateChangedMessage(DirectionsMenuStage stage)
            : m_stage(stage)
        {

        }

        const DirectionsMenuStage& DirectionsMenuStateChangedMessage::GetDirectionsMenuStage() const
        {
            return m_stage;
        }
    }
}
