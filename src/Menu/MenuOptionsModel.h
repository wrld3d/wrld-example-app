// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Types.h"
#include "Menu.h"
#include "IMenuOptionsModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        class MenuOptionsModel : public IMenuOptionsModel, private Eegeo::NonCopyable
        {
        private:
            Menu::IMenuModel& m_menu;
            std::map<std::string, Menu::IMenuOption*> m_options;
            
        public:
            MenuOptionsModel(Menu::IMenuModel& menu);
            
            ~MenuOptionsModel();
            
            void AddItem(const std::string& uniqueIdentifier,
                         const std::string& name,
                         const std::string& details,
                         const std::string& icon,
                         Menu::IMenuOption* pOption);
            
            void RemoveItem(const std::string& uniqueIdentifier);
            
        private:
            
            void EraseOption(const std::string& uniqueIdentifier);
        };
    }
}
