// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class ISwallowSearchMenuModule
                {
                public:
                    virtual ~ISwallowSearchMenuModule() { }
                    
                    virtual Menu::View::IMenuModel& GetMeetingRoomsMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetWorkingGroupsMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetFacilitiesMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetOfficesMenuModel() const = 0;
                    
                };
            }
        }
    }
}