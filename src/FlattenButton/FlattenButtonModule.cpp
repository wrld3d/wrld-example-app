// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonModule.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonModule::FlattenButtonModule(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                 Eegeo::Helpers::IIdentityProvider& identityProvider)
        {
            m_pModel = Eegeo_NEW(FlattenButtonModel)(environmentFlatteningService);
            m_pViewModel = Eegeo_NEW(FlattenButtonViewModel)(identityProvider.GetNextIdentity(), false);
        }
        
        FlattenButtonModule::~FlattenButtonModule()
        {
            Eegeo_DELETE m_pViewModel;
            Eegeo_DELETE m_pModel;
        }
        
        IFlattenButtonModel& FlattenButtonModule::GetFlattenButtonModel() const
        {
            return *m_pModel;
        }
        
        IFlattenButtonViewModel& FlattenButtonModule::GetFlattenButtonViewModel() const
        {
            return *m_pViewModel;
        }
        
        ScreenControlViewModel::IScreenControlViewModel& FlattenButtonModule::GetScreenControlViewModel() const
        {
            return m_pViewModel->GetScreenControlViewModel();
        }
    }
}
