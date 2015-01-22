// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Menu.h"

namespace ExampleApp
{
	namespace Menu
	{
		class IMenuOptionsModel
		{
		public:
			virtual ~IMenuOptionsModel() { }

			virtual void AddItem(const std::string& uniqueIdentifier,
			                     const std::string& name,
			                     const std::string& details,
			                     const std::string& icon,
			                     Menu::IMenuOption* pOption) = 0;

			virtual void RemoveItem(const std::string& uniqueIdentifier) = 0;
		};
	}
}
