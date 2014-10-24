// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiCreationDetailsViewModule.h"
#include "PoiCreationDetailsViewIncludes.h"
#include "PoiCreationDetails.h"
#include "PoiCreation.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class PoiCreationDetailsViewModule : public IPoiCreationDetailsViewModule
        {
        public:
            PoiCreationDetailsViewModule(PoiCreation::IPoiCreationModel& poiCreationModel,
                                         IPoiCreationDetailsViewModel& poiCreationDetailsViewModel);
            
            ~PoiCreationDetailsViewModule();
            
            PoiCreationDetailsViewController& GetPoiCreationDetailsViewController() const;
            PoiCreationDetailsView& GetPoiCreationDetailsView() const;
        
        private:
            PoiCreationDetailsViewController* m_pController;
        };
    }
}