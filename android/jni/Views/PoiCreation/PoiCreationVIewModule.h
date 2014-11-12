// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiCreationViewModule.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "PoiCreation.h"
#include "PoiCreationDetails.h"
#include "PoiCreationViewIncludes.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
    	class PoiCreationViewModule : public IPoiCreationViewModule, private Eegeo::NonCopyable
        {
        private:
        	PoiCreationButtonViewController* m_pButtonViewController;
        	PoiCreationConfirmationViewController* m_pConfirmationViewController;

        public:
        	PoiCreationViewModule(
            	AndroidNativeState& nativeState,
            	PoiCreation::IPoiCreationModel& model,
            	PoiCreation::IPoiCreationButtonViewModel& buttonViewModel,
            	PoiCreation::IPoiCreationConfirmationViewModel& confirmationViewModel,
            	PoiCreationDetails::IPoiCreationDetailsViewModel& detailsViewModel
            );

            ~PoiCreationViewModule();
        };
    }
}
