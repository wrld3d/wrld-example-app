// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinItemModel;
            class IWorldPinsModule;
            class IWorldPinsFactory;
            class IWorldPinsService;
            class IWorldPinsRepository;
            class IWorldPinSelectionHandler;
            class IWorldPinVisibilityStateChangedHandler;
            class IWorldPinsVisibilityController;
            class IWorldPinsInFocusModel;
            class IWorldPinIconMappingFactory;
            class IWorldPinIconMapping;
            
            class IWorldPinsFocusModule;
        }
        class WorldPinsVisibilityMessage;
        class WorldPinsSelectedFocussedMessage;
        class WorldPinHiddenStateChangedMessage;
    }
}
