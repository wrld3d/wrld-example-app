// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinsModule
            {
            public:
                virtual ~IMyPinsModule() { }
                
                virtual IMyPinsService& GetMyPinsService() const = 0;
                
                virtual Menu::View::IMenuModel& GetMyPinsMenuModel() const = 0;
            };
        }
    }
}
