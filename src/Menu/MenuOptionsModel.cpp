// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include "MenuOptionsModel.h"
#include "Menu.h"
#include "IMenuModel.h"

namespace ExampleApp
{
namespace Menu
{
MenuOptionsModel::MenuOptionsModel(Menu::IMenuModel& menu)
	: m_menu(menu)
{

}

MenuOptionsModel::~MenuOptionsModel()
{
	while(m_menu.GetItemCount() != 0)
	{
		ExampleApp::Menu::MenuItemModel item = m_menu.GetItemAtIndex(0);
		EraseOption(item.Identifier());
		m_menu.RemoveItem(item);
	}
}

void MenuOptionsModel::AddItem(const std::string& uniqueIdentifier,
                               const std::string& name,
                               const std::string& details,
                               const std::string& icon,
                               Menu::IMenuOption* pOption)
{
	std::map<std::string, Menu::IMenuOption*>::iterator optionIt = m_options.find(uniqueIdentifier);

	Eegeo_ASSERT(optionIt == m_options.end(),
	             "Attempting to add item %s to menu, but %s is already in menu.\n",
	             uniqueIdentifier.c_str(), uniqueIdentifier.c_str());
	m_options[uniqueIdentifier] = pOption;
	ExampleApp::Menu::MenuItemModel menuItem(uniqueIdentifier, name, details, icon, pOption);
	m_menu.AddItem(menuItem);
}

void MenuOptionsModel::RemoveItem(const std::string& uniqueIdentifier)
{
	for(size_t i = 0; i < m_menu.GetItemCount(); ++ i)
	{
		ExampleApp::Menu::MenuItemModel item = m_menu.GetItemAtIndex(i);

		if(item.Identifier() == uniqueIdentifier)
		{
			EraseOption(uniqueIdentifier);
			m_menu.RemoveItem(item);
			return;
		}
	}
}

void MenuOptionsModel::EraseOption(const std::string& uniqueIdentifier)
{
	std::map<std::string, Menu::IMenuOption*>::iterator optionIt = m_options.find(uniqueIdentifier);

	Eegeo_ASSERT(optionIt != m_options.end(),
	             "Attempting to remove item %s from menu, but %s is not in menu.\n",
	             uniqueIdentifier.c_str(), uniqueIdentifier.c_str());

	Menu::IMenuOption* pOption = optionIt->second;
	m_options.erase(optionIt);
	Eegeo_DELETE pOption;
}
}
}
