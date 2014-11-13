// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationInitiationViewModule
        {
        public:
            
            virtual ~IMyPinCreationInitiationViewModule() { }
            
            virtual MyPinCreationInitiationViewController& GetMyPinCreationInitiationViewController() const = 0;
            virtual MyPinCreationInitiationView& GetMyPinCreationInitiationView() const = 0;
        };
    }
}
