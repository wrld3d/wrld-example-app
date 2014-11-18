// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWorldPinsModule.h"
#include "WorldPins.h"
#include "Pins.h"
#include "PinController.h"
#include "Rendering.h"
#include "Camera.h"
#include "NativeToUiMessageBus.h"
#include "WorldPinInFocusObserver.h"
#include "IIdentity.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsModule : public IWorldPinsModule
        {
            IWorldPinsFactory* m_pWorldPinsFactory;
            IWorldPinsService* m_pWorldPinsService;
            IWorldPinsRepository* m_pWorldPinsRepository;
            IWorldPinsScaleController* m_pWorldPinsScaleController;
            WorldPinInFocusViewModel* m_pWorldPinsInFocusViewModel;
            IWorldPinsInFocusController* m_pWorldPinsInFocusController;
            WorldPinInFocusObserver* m_pWorldPinInFocusObserver;
            
        public:
            WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                            Eegeo::Pins::PinController& pinController,
                            const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            const Eegeo::Rendering::ScreenProperties& screenProperties,
                            Eegeo::Helpers::IIdentityProvider& identityProvider,
                            ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~WorldPinsModule();
            
            IWorldPinsService& GetWorldPinsService() const;
            
            IWorldPinsFactory& GetWorldPinsFactory() const;
            
            IWorldPinsScaleController& GetWorldPinsScaleController() const;
            
            IWorldPinInFocusViewModel& GetWorldPinInFocusViewModel() const;
            
            IWorldPinsInFocusController& GetWorldPinsInFocusController() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const;
        };
    }
}
