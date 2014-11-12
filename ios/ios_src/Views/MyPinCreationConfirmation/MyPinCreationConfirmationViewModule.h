// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "IMyPinCreationConfirmationViewModule.h"
#include "MyPinCreationDetails.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationConfirmationViewModule: public IMyPinCreationConfirmationViewModule, private Eegeo::NonCopyable
        {
        private:
            MyPinCreationConfirmationViewController* m_pController;
            
        public:
            MyPinCreationConfirmationViewModule(IMyPinCreationModel& model,
                                              IMyPinCreationConfirmationViewModel& viewModel,
                                              IMyPinCreationCompositeViewModel& compositeViewModel,
                                              MyPinCreationDetails::IMyPinCreationDetailsViewModel& MyPinCreationDetailsViewModel,
                                              const Eegeo::Rendering::ScreenProperties& screenProperties);
            
            ~MyPinCreationConfirmationViewModule();
            
            MyPinCreationConfirmationViewController& GetMyPinCreationConfirmationViewController() const;
            
            MyPinCreationConfirmationView& GetMyPinCreationConfirmationView() const;
        };
    }
}
