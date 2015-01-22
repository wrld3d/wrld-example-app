// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsVIewModel.h"
#include "Reaction.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class MyPinCreationDetailsModule : public IMyPinCreationDetailsModule
        {
        public:
            MyPinCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                       Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~MyPinCreationDetailsModule();
            
            IMyPinCreationDetailsViewModel& GetMyPinCreationDetailsViewModel() const;
            
            OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
            
        private:
            MyPinCreationDetailsViewModel* m_pMyPinCreationDetailsViewModel;
            
        };
    }
}