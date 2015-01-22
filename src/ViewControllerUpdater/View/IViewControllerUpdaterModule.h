// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class IViewControllerUpdaterModule
            {
            public:
                virtual ~IViewControllerUpdaterModule() { }

                virtual IViewControllerUpdaterModel& GetViewControllerUpdaterModel() const = 0;
            };
        }
    }
}
