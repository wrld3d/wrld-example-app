// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"
#include "Compass.h"
#include "ICompassViewModule.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
        {
        private:
            CompassViewController* m_pController;
            
        public:
            CompassViewModule(ICompassModel& model,
                              ICompassViewModel& viewModel,
                              const Eegeo::Rendering::ScreenProperties& screenProperties);
            
            ~CompassViewModule();
            
            CompassViewController& GetCompassViewController() const;
            
            CompassView& GetCompassView() const;
        };
    }
}
