// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiCreationDetailsViewModule.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "PoiCreationDetails.h"
#include "PoiCreation.h"
#include "PoiCreationDetailsViewIncludes.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
    	class PoiCreationDetailsViewModule : public IPoiCreationDetailsViewModule, private Eegeo::NonCopyable
        {
        private:
    		PoiCreationDetailsViewController* m_pViewController;

        public:
    		PoiCreationDetailsViewModule(
            	AndroidNativeState& nativeState,
            	PoiCreation::IPoiCreationModel& model,
            	PoiCreationDetails::IPoiCreationDetailsViewModel& viewModel
            );

            ~PoiCreationDetailsViewModule();
        };
    }
}
