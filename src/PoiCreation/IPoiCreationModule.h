// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreation.h"
#include "Camera.h"
#include "ScreenControlViewModelIncludes.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class IPoiCreationModule
        {
        public:
            virtual ~IPoiCreationModule(){}
            
            virtual IPoiCreationModel& GetPoiCreationModel() const = 0;
            virtual IPoiCreationButtonViewModel& GetPoiCreationButtonViewModel() const = 0;
            virtual IPoiCreationConfirmationViewModel& GetPoiCreationConfirmationViewModel() const = 0;
            virtual IPoiCreationCompositeViewModel& GetPoiCreationCompositeViewModel() const = 0;
            
            virtual ScreenControlViewModel::IScreenControlViewModel& GetButtonScreenControlViewModel() const = 0;
            virtual ScreenControlViewModel::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const = 0;
        };
    }
}