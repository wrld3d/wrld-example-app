// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "PoiCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "PoiCreation.h"
#include "IPoiCreationConfirmationViewModule.h"
#include "PoiCreationDetails.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationConfirmationViewModule: public IPoiCreationConfirmationViewModule, private Eegeo::NonCopyable
        {
        private:
            PoiCreationConfirmationViewController* m_pController;
            
        public:
            PoiCreationConfirmationViewModule(IPoiCreationModel& model,
                                              IPoiCreationConfirmationViewModel& viewModel,
                                              IPoiCreationCompositeViewModel& compositeViewModel,
                                              PoiCreationDetails::IPoiCreationDetailsViewModel& poiCreationDetailsViewModel,
                                              const Eegeo::Rendering::ScreenProperties& screenProperties);
            
            ~PoiCreationConfirmationViewModule();
            
            PoiCreationConfirmationViewController& GetPoiCreationConfirmationViewController() const;
            
            PoiCreationConfirmationView& GetPoiCreationConfirmationView() const;
        };
    }
}
