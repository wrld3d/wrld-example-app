// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorsExplorerModule.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "IIdentity.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
            {
            public:
                InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                        Eegeo::Helpers::IIdentityProvider& identityProvider,
                                        ExampleAppMessaging::TMessageBus& messageBus);
                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
            private:
                
                InteriorsExplorerModel* m_pModel;
                View::InteriorsExplorerViewModel* m_pViewModel;
            };
        }
    }
}