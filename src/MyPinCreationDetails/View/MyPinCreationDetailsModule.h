// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModel.h"
#include "Reaction.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsModule : public IMyPinCreationDetailsModule
            {
            public:
                MyPinCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                           Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~MyPinCreationDetailsModule();

                IMyPinCreationDetailsViewModel& GetMyPinCreationDetailsViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;

            private:
                MyPinCreationDetailsViewModel* m_pMyPinCreationDetailsViewModel;

            };
        }
    }
}
