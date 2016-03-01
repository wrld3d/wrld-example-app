// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "InteriorsExplorerViewIncludes.h"
#include "BidirectionalBus.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "IIdentity.h"
#include "Interiors.h"
#include "ScreenControlViewModelIncludes.h"
#include "IInteriorsExplorerViewModule.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerViewModule : public IInteriorsExplorerViewModule
            {
            private:
                InteriorsExplorerController* m_pController;
                InteriorsExplorerView* m_pView;
                
                
            public:
                InteriorsExplorerViewModule(InteriorsExplorerViewModel& viewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                            ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                            ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                            ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                            ScreenControl::View::IScreenControlViewModel& compassViewModel,
                                            ScreenControl::View::IScreenControlViewModel& watermarkViewModel,
                                            Eegeo::Helpers::IdentityProvider& identityProvider);
                
                ~InteriorsExplorerViewModule();
                
                InteriorsExplorerController& GetController() const;
                
                InteriorsExplorerView& GetView() const;
            };
        }
    }
}
