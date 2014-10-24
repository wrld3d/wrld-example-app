// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class IPoiCreationConfirmationViewModel : public ScreenControlViewModel::IScreenControlViewModel
        {
        public:
            
            virtual ~IPoiCreationConfirmationViewModel() { }
        };
    }
}
