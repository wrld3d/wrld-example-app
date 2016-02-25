// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IMenuOption.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuItemModel
            {
            private:
                std::string m_identifier;
                std::string m_name;
                std::string m_details;
                std::string m_icon;
                IMenuOption* m_pOption;

            public:
                MenuItemModel(const std::string& identifier,
                              const std::string& name,
                              const std::string& details,
                              const std::string& icon,
                              IMenuOption* pOption);

                ~MenuItemModel();

                const std::string& Identifier() const;

                const std::string& Name() const;

                const std::string& Details() const;

                const std::string& Icon() const;

                std::string SerializeJson() const;
                
                IMenuOption& MenuOption();
            };

            inline bool operator==(const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return lhs.Identifier() == rhs.Identifier();
            }
            inline bool operator!=(const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return !operator==(lhs,rhs);
            }
            inline bool operator< (const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return lhs.Identifier() < rhs.Identifier();
            }
            inline bool operator> (const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return  operator< (rhs,lhs);
            }
            inline bool operator<=(const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return !operator> (lhs,rhs);
            }
            inline bool operator>=(const MenuItemModel& lhs, const MenuItemModel& rhs)
            {
                return !operator< (lhs,rhs);
            }
        }
    }
}
