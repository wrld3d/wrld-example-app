// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace PoiCreation
    {
        class IPoiCreationButtonViewModule
        {
        public:
            
            virtual ~IPoiCreationButtonViewModule() { }
            
            virtual PoiCreationButtonViewController& GetPoiCreationButtonViewController() const = 0;
            virtual PoiCreationButtonView& GetPoiCreationButtonView() const = 0;
        };
    }
}
