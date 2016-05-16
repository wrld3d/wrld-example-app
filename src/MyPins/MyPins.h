// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinModel;
            class MyPinModel;

            class IMyPinsRepository;
            class MyPinsRepository;

            class IMyPinsModule;
            class MyPinsModule;

            class IMyPinsService;
            class MyPinsService;
            class MyPinsWebService;

            class MyPinsFileIO;

            class MyPinsRepositoryObserver;

            class IMyPinSelectionHandlerFactory;
            class MyPinSelectionHandlerFactory;
            class MyPinSelectionHandler;
            class MyPinSelectedMessageHandler;
            
            class IMyPinVisibilityStateChangedHandlerFactory;
            class MyPinVisibilityStateChangedHandlerFactory;
            class MyPinVisibilityStateChangedHandler;
            
            class IMyPinBoundObject;
            class IMyPinBoundObjectFactory;
            class IMyPinBoundObjectRepository;
        }

        namespace View
        {
            class MyPinAddedToMenuObserver;
            class MyPinRemovedFromMenuObserver;
        }

        class MyPinSelectedMessage;

    }
}
