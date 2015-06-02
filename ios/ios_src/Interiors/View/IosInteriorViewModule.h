// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "IosInteriorViewIncludes.h"
#include "InteriorsViewController.h"
#include "BidirectionalBus.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "IMyPinCreationConfirmationViewModule.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "InteriorsViewModel.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            class IosInteriorViewModule : private Eegeo::NonCopyable
            {
            private:
                InteriorsViewController* m_pController;
                IosInteriorView* m_pView;
                InteriorsViewModel* m_pViewModel;
                
                
            public:
                IosInteriorViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                      Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                      MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                      ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                      ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel,
                                      ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                      ScreenControl::View::IScreenControlViewModel& compassViewModel,
                                      const Eegeo::Rendering::ScreenProperties& screenProperties,
                                      Eegeo::Helpers::IdentityProvider& identityProvider);
                
                ~IosInteriorViewModule();
                
                InteriorsViewController& GetController() const;
                
                IosInteriorView& GetView() const;
            };
        }
    }
}
