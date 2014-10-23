// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "FlattenButton.h"
#include "Rendering.h"
#include "FlattenButtonModule.h"
#include "IFlattenButtonModule.h"
#include "IIdentity.h"
#include "FlattenButtonViewModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonModule : public IFlattenButtonModule, private Eegeo::NonCopyable
        {
        private:
            FlattenButtonViewModel* m_pViewModel;
            IFlattenButtonModel* m_pModel;
            
        public:
            FlattenButtonModule(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                Eegeo::Helpers::IIdentityProvider& identityProvider);
            
            ~FlattenButtonModule();
            
            IFlattenButtonModel& GetFlattenButtonModel() const;
            
            IFlattenButtonViewModel& GetFlattenButtonViewModel() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const;
        };

    }
}
