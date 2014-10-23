// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICompassViewModule.h"
#include "AndroidNativeState.h"
#include "Types.h"
#include "Compass.h"
#include "CompassViewIncludes.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
        {
        private:
        	CompassViewController* m_pController;

        public:
        	CompassViewModule(
            	AndroidNativeState& nativeState,
        		Compass::ICompassModel& model,
        		Compass::ICompassViewModel& viewModel
            );

            ~CompassViewModule();
        };
    }
}
