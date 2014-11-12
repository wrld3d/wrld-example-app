// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewModule.h"
#include "PoiCreationDetailsViewController.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
    	PoiCreationDetailsViewModule::PoiCreationDetailsViewModule(
            	AndroidNativeState& nativeState,
            	PoiCreation::IPoiCreationModel& model,
            	PoiCreationDetails::IPoiCreationDetailsViewModel& viewModel
            )
    	{
    		m_pViewController = Eegeo_NEW(PoiCreationDetailsViewController)(
    				nativeState,
    				model,
    				viewModel
    			);
    	}

    	PoiCreationDetailsViewModule::~PoiCreationDetailsViewModule()
    	{
    		Eegeo_DELETE m_pViewController;
    	}
    }
}
