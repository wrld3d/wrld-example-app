// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonModule.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonModule::FlattenButtonModule(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                 Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                 ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        {
            m_pModel = Eegeo_NEW(FlattenButtonModel)(environmentFlatteningService);
            m_pViewModel = Eegeo_NEW(FlattenButtonViewModel)(identityProvider.GetNextIdentity(), false);
            m_pFlattenButtonViewStateChangedObserver = Eegeo_NEW(FlattenButtonViewStateChangedObserver)(*m_pModel, uiToNativeMessageBus);
            m_pFlattenButtonModelStateChangedObserver = Eegeo_NEW(FlattenButtonModelStateChangedObserver)(*m_pModel, nativeToUiMessageBus);
        }
        
        FlattenButtonModule::~FlattenButtonModule()
        {
            Eegeo_DELETE m_pFlattenButtonModelStateChangedObserver;
            Eegeo_DELETE m_pFlattenButtonViewStateChangedObserver;
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
