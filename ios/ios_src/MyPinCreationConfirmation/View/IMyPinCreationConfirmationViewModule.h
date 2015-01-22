// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationConfirmationViewModule
        {
        public:
            
            virtual ~IMyPinCreationConfirmationViewModule() { }
            
            virtual MyPinCreationConfirmationViewController& GetMyPinCreationConfirmationViewController() const = 0;
            virtual MyPinCreationConfirmationView& GetMyPinCreationConfirmationView() const = 0;
        };
    }
}
