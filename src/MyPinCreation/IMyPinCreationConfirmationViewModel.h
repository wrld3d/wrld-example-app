// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationConfirmationViewModel : public ScreenControlViewModel::IScreenControlViewModel
        {
        public:
            
            virtual ~IMyPinCreationConfirmationViewModel() { }
            virtual bool TryOpen() = 0;
            virtual void Close() = 0;
        };
    }
}
