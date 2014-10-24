// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreationDetails.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class IPoiCreationDetailsModule
        {
        public:
            ~IPoiCreationDetailsModule(){ }
            
            virtual IPoiCreationDetailsViewModel& GetPoiCreationDetailsViewModel() const = 0;
            
            virtual OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
        };
    }
}