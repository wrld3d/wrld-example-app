// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationConfirmationViewModule
            {
            public:

                virtual ~IMyPinCreationConfirmationViewModule() { }

                virtual MyPinCreationConfirmationController& GetMyPinCreationConfirmationController() const = 0;
                virtual MyPinCreationConfirmationView& GetMyPinCreationConfirmationView() const = 0;
            };
        }
    }
}
