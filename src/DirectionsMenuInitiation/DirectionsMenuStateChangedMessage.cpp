// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        DirectionsMenuStateChangedMessage::DirectionsMenuStateChangedMessage(DirectionsMenuStage stage, bool close)
        : m_stage(stage)
        , m_closeForWorldPin(close)
        {

        }

        const DirectionsMenuStage& DirectionsMenuStateChangedMessage::GetDirectionsMenuStage() const
        {
            return m_stage;
        }
        
        const bool DirectionsMenuStateChangedMessage::GetCloseForWorldPin() const
        {
            return m_closeForWorldPin;
        }
    }
}
