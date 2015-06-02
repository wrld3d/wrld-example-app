//
//  IosInteriorViewModule.cpp
//  ExampleApp
//
//  Created by eeGeo QA on 29/05/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#include "IosInteriorViewModule.h"
#include "ScreenProperties.h"
#include "IosInteriorView.h"
#include "IosInteriorViewInterop.h"
#include "ScreenControlViewModelBase.h"

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            IosInteriorViewModule::IosInteriorViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                         Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                         MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                                         ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                                         ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel,
                                                         ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                                         ScreenControl::View::IScreenControlViewModel& compassViewModel,
                                                         const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                         Eegeo::Helpers::IdentityProvider& identityProvider)
            {
                // IH: This is hacky. Attempting to get the UI done for an impending board meeting but this isn't how we want to do this.
                //     For e.g. the view model should probably be some SDK model guy created in MEA.
                //     We'd also probably create some composite view model that would take care of the appearance of UI elements from other domains.
                m_pView = [[IosInteriorView alloc] initWithParams: screenProperties.GetScreenWidth(): screenProperties.GetScreenHeight(): screenProperties.GetPixelScale()];
                
                const bool initiallyOnScreen = false;
                m_pViewModel = Eegeo_NEW(InteriorsViewModel)(initiallyOnScreen, identityProvider.GetNextIdentity());
                
                m_pController = Eegeo_NEW(InteriorsViewController)(*[m_pView getInterop],
                                                                   interiorsController,
                                                                   *m_pViewModel,
                                                                   messageBus,
                                                                   initiationViewModel,
                                                                   secondaryMenuViewModel,
                                                                   searchResultMenuViewModel,
                                                                   flattenViewModel,
                                                                   compassViewModel);
                

            }
            
            IosInteriorViewModule::~IosInteriorViewModule()
            {
                Eegeo_DELETE m_pController;
                
                Eegeo_DELETE m_pViewModel;
                
                [m_pView release];

            }
            
            InteriorsViewController& IosInteriorViewModule::GetController() const
            {
                return *m_pController;
            }
            
            IosInteriorView& IosInteriorViewModule::GetView() const
            {
                return *m_pView;
            }
        }
    }
}