// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModule.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            FlattenButtonModule::FlattenButtonModule(MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                     Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(FlattenButtonModel)(mapModeModel);
                m_pViewModel = Eegeo_NEW(View::FlattenButtonViewModel)(identityProvider.GetNextIdentity(), false);
                m_pFlattenButtonViewStateChangedObserver = Eegeo_NEW(FlattenButtonViewStateChangedObserver)(*m_pModel, messageBus);
                m_pFlattenButtonModelStateChangedObserver = Eegeo_NEW(FlattenButtonModelStateChangedObserver)(*m_pModel, messageBus);
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

            View::IFlattenButtonViewModel& FlattenButtonModule::GetFlattenButtonViewModel() const
            {
                return *m_pViewModel;
            }

            ScreenControl::View::IScreenControlViewModel& FlattenButtonModule::GetScreenControlViewModel() const
            {
                return m_pViewModel->GetScreenControlViewModel();
            }
        }
    }
}
