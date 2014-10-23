// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        class IViewControllerUpdaterModule
        {
        public:
            virtual ~IViewControllerUpdaterModule() { }
            
            virtual IViewControllerUpdaterModel& GetViewControllerUpdaterModel() const = 0;
        };
    }
}
