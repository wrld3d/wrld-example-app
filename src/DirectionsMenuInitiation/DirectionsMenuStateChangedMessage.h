// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DirectionsMenuStage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        class DirectionsMenuStateChangedMessage
        {
        public:
            DirectionsMenuStateChangedMessage(DirectionsMenuStage stage, bool close);

            const DirectionsMenuStage& GetDirectionsMenuStage() const;
            const bool GetCloseForWorldPin() const;

        private:
            DirectionsMenuStage m_stage;
            bool m_closeForWorldPin;
        };
    }
}
