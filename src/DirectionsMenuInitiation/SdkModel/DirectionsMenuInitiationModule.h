// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DirectionsMenuInitiation.h"
#include "IDirectionsMenuInitiationModule.h"
#include "Modules.h"
#include "VectorMathDecl.h"
#include "Camera.h"
#include "Rendering.h"
#include "Terrain.h"
#include "IIdentity.h"
#include "Menu.h"
#include "Search.h"
#include "IdTypes.h"
#include "BidirectionalBus.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace SdkModel
        {
            class DirectionsMenuInitiationModule : public IDirectionsMenuInitiationModule
            {
            public:
                DirectionsMenuInitiationModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                    ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                    ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                                    ExampleAppMessaging::TMessageBus& messageBus,
                                    Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~DirectionsMenuInitiationModule();

                View::IDirectionsMenuInitiationViewModel& GetDirectionsMenuInitiationViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetInitiationScreenControlViewModel() const;

            private:
                View::DirectionsMenuInitiationViewModel* m_pDirectionsMenuInitiationViewModel;
            };
        }
    }
}
