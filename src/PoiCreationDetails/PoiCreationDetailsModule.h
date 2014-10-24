// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiCreationDetailsModule.h"
#include "PoiCreationDetailsVIewModel.h"
#include "Reaction.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class PoiCreationDetailsModule : public IPoiCreationDetailsModule
        {
        public:
            PoiCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                     Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~PoiCreationDetailsModule();
            
            IPoiCreationDetailsViewModel& GetPoiCreationDetailsViewModel() const;
            
            OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
            
        private:
            PoiCreationDetailsViewModel* m_pPoiCreationDetailsViewModel;
            
        };
    }
}