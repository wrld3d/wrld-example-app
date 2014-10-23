// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "FlattenButtonViewController.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
    	FlattenButtonViewModule::FlattenButtonViewModule(
            	AndroidNativeState& nativeState,
				FlattenButton::IFlattenButtonModel& model,
        		FlattenButton::IFlattenButtonViewModel& viewModel
            )
    	{
    		m_pController = Eegeo_NEW(FlattenButtonViewController)(
    				nativeState,
    				model,
    				viewModel);
    	}

    	FlattenButtonViewModule::~FlattenButtonViewModule()
    	{
    		Eegeo_DELETE m_pController;
    	}
    }
}
