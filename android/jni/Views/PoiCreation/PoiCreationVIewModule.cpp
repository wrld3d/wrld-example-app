// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationViewModule.h"
#include "PoiCreationButtonViewController.h"
#include "PoiCreationConfirmationViewController.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
    	PoiCreationViewModule::PoiCreationViewModule(
            	AndroidNativeState& nativeState,
            	PoiCreation::IPoiCreationModel& model,
            	PoiCreation::IPoiCreationButtonViewModel& buttonViewModel,
            	PoiCreation::IPoiCreationConfirmationViewModel& confirmationViewModel,
            	PoiCreationDetails::IPoiCreationDetailsViewModel& detailsViewModel
            )
    	{
    		m_pButtonViewController = Eegeo_NEW(PoiCreationButtonViewController)(nativeState, model, buttonViewModel);
    		m_pConfirmationViewController = Eegeo_NEW(PoiCreationConfirmationViewController)(nativeState, model, confirmationViewModel, detailsViewModel);
    	}

    	PoiCreationViewModule::~PoiCreationViewModule()
    	{
    		Eegeo_DELETE m_pConfirmationViewController;
    		Eegeo_DELETE m_pButtonViewController;
    	}
    }
}
