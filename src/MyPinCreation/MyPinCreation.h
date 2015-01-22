// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class IMyPinCreationModule;
            class MyPinCreationModule;

            class IMyPinCreationModel;
            class MyPinCreationModel;
        }

        namespace View
        {
            class IMyPinCreationInitiationViewModel;
            class MyPinCreationInitiationViewModel;

            class IMyPinCreationInitiationView;
            class MyPinCreationInitiationController;

            class IMyPinCreationConfirmationViewModel;
            class MyPinCreationConfirmationViewModel;

            class IMyPinCreationConfirmationView;
            class MyPinCreationConfirmationController;

            class IMyPinCreationCompositeViewModel;
            class MyPinCreationCompositeViewModel;
        }

        namespace PoiRing
        {
            namespace SdkModel
            {
                class IPoiRingModule;
                class PoiRingModule;

                class PoiRingView;
                class PoiRingRenderable;

                class IPoiRingController;
                class PoiRingController;

                class IPoiRingTouchController;
                class PoiRingTouchController;
            }
        }
    }
}
