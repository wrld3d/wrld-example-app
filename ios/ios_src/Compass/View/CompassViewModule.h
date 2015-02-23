// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"
#include "Compass.h"
#include "ICompassViewModule.h"
#include "BidirectionalBus.h"
#include "CompassController.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
            {
            private:
                CompassController* m_pController;
                CompassView* m_pView;

            public:
                CompassViewModule(ICompassViewModel& viewModel,
                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                  ExampleAppMessaging::TMessageBus& messageBus);

                ~CompassViewModule();

                CompassController& GetCompassController() const;

                CompassView& GetCompassView() const;
            };
        }
    }
}
