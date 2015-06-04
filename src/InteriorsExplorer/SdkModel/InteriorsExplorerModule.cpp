// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "IScreenControlViewModel.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorsController, messageBus);
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pViewModel;
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                return *m_pViewModel;
            }
        }
    }
}