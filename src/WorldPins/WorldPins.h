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
            class IWorldPinsScaleController;
            class IWorldPinsFloorHeightController;
            class IWorldPinsInFocusModel;
            class IWorldPinsInFocusController;
        }

        namespace View
        {
            class IWorldPinInFocusViewModel;
            class WorldPinInFocusViewModel;
            class IWorldPinOnMapView;
            class WorldPinOnMapController;
        }

        class WorldPinsVisibilityMessage;
    }
}
