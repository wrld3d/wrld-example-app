// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorExplorerConnectionChangedObserver.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorExplorerConnectionController
            {
            public:
                InteriorExplorerConnectionController(InteriorExplorerConnectionChangedObserver& interiorExplorerConnectionChangedObserver);
                ~InteriorExplorerConnectionController();

                void Update(float dt);

            private:
                InteriorExplorerConnectionChangedObserver& m_pInteriorExplorerConnectionChangedObserver;
                bool m_hasEjectedUser;
                const float m_ssidTimeout;
                float m_timeSinceAuthorisedForInterior;
            };
        }
    }
}
