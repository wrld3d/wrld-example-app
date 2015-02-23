// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class IFlattenButtonViewModule
            {
            public:

                virtual ~IFlattenButtonViewModule() { }

                virtual FlattenButtonView& GetFlattenButtonView() const = 0;
            };
        }
    }
}
