// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class ILaxSearchMenuModule
                {
                public:
                    virtual ~ILaxSearchMenuModule() { }
                    
                    virtual Menu::View::IMenuModel& GetMeetingRoomsMenuModel() const = 0;
                    
                    virtual Menu::View::IMenuModel& GetFoodMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetShoppingMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetElevatorMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetStairsMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetEscalatorMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetRestroomMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetTddpayphoneMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetAtmMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetPayphoneMenuModel() const = 0;
                    virtual Menu::View::IMenuModel& GetGateseMenuModel() const = 0;
                    
                    
//                    virtual Menu::View::IMenuModel& GetWorkingGroupsMenuModel() const = 0;
//                    virtual Menu::View::IMenuModel& GetFacilitiesMenuModel() const = 0;
//                    virtual Menu::View::IMenuModel& GetOfficesMenuModel() const = 0;
//                    virtual Menu::View::IMenuModel& GetPersonMenuModel() const = 0;
                    
                };
            }
        }
    }
}