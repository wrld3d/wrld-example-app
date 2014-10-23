// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassViewModule.h"
#include "CompassViewController.h"

namespace ExampleApp
{
    namespace Compass
    {
    	CompassViewModule::CompassViewModule(
            	AndroidNativeState& nativeState,
        		Compass::ICompassModel& model,
        		Compass::ICompassViewModel& viewModel
            )
    	{
    		m_pController = Eegeo_NEW(CompassViewController)(
    				nativeState,
    				model,
    				viewModel);
    	}

    	CompassViewModule::~CompassViewModule()
    	{
    		Eegeo_DELETE m_pController;
    	}
    }
}
