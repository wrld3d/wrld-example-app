// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuOption
            {
            public:
                virtual ~IMenuOption() { }

                virtual void Select() = 0;
            };
        }
    }
}
