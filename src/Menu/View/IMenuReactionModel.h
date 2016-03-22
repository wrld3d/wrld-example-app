// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuReactionModel
            {
            public:
                virtual ~IMenuReactionModel() {};

                virtual bool GetShouldCloseMenu() const = 0;
                virtual bool GetShouldOpenMenu() const = 0;
            };
        }
    }
}
