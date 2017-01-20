// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractModeStateChangedMessage.h"
#include "AttractModeStates.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        AttractModeStateChangedMessage::AttractModeStateChangedMessage(const SdkModel::States::State state)
            : m_state(state)
        {
        }

        const SdkModel::States::State AttractModeStateChangedMessage::State() const
        {
            return m_state;
        }
    }
}
