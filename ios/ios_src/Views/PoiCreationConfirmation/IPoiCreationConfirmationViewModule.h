// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace PoiCreation
    {
        class IPoiCreationConfirmationViewModule
        {
        public:
            
            virtual ~IPoiCreationConfirmationViewModule() { }
            
            virtual PoiCreationConfirmationViewController& GetPoiCreationConfirmationViewController() const = 0;
            virtual PoiCreationConfirmationView& GetPoiCreationConfirmationView() const = 0;
        };
    }
}
