// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AttractModeStates.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        class AttractModeStateChangedMessage
        {
        public:
            AttractModeStateChangedMessage(const SdkModel::States::State state);
            const SdkModel::States::State State() const;

        private:
            const SdkModel::States::State m_state;
        };
    }
}
