// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include "DirectionsMenuOptionsModel.h"
#include "IMenuModel.h"
#include "DirectionsMenuItemModel.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            DirectionsMenuOptionsModel::DirectionsMenuOptionsModel(IMenuModel& menu)
                : MenuOptionsModel(menu)
            {

            }

            DirectionsMenuOptionsModel::~DirectionsMenuOptionsModel()
            {
                while(m_menu.GetItemCount() != 0)
                {
                    MenuItemModel item = m_menu.GetItemAtIndex(0);
                    EraseOption(item.Identifier());
                    m_menu.RemoveItem(item);
                }
            }

            void DirectionsMenuOptionsModel::AddItem(const std::string& uniqueIdentifier,
                                           const std::string& name,
                                           const std::string& details,
                                           const std::string& icon,
                                           const std::string& duration,
                                           IMenuOption* pOption)
            {
                std::map<std::string, IMenuOption*>::iterator optionIt = m_options.find(uniqueIdentifier);

                Eegeo_ASSERT(optionIt == m_options.end(),
                             "Attempting to add item %s to menu, but %s is already in menu.\n",
                             uniqueIdentifier.c_str(), uniqueIdentifier.c_str());
                m_options[uniqueIdentifier] = pOption;
                DirectionsMenuItemModel menuItem(uniqueIdentifier, name, details, icon,duration, pOption);
                m_menu.AddItem(menuItem);
            }
        }
    }
}
