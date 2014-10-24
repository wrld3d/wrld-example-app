// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreationDetailsViewIncludes.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class IPoiCreationDetailsViewModule
        {
        public:
            
            virtual ~IPoiCreationDetailsViewModule() { }
            
            virtual PoiCreationDetailsViewController& GetPoiCreationDetailsViewController() const = 0;
            virtual PoiCreationDetailsView& GetPoiCreationDetailsView() const = 0;
        };
    }
}