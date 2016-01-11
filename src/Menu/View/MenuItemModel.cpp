// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuItemModel.h"
#include "Types.h"
#include "MenuJsonSerializer.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuItemModel::MenuItemModel(const std::string& identifier,
                                         const std::string& name,
                                         const std::string& details,
                                         const std::string& icon,
                                         IMenuOption* pOption)
                : m_identifier(identifier)
                , m_name(name)
                , m_details(details)
                , m_icon(icon)
                , m_pOption(pOption)
            {
                Eegeo_ASSERT(m_pOption != NULL, "MenuItemModel must be provided with a non-null menu option.")
            }

            MenuItemModel::~MenuItemModel()
            {

            }

            std::string MenuItemModel::SerializeJson() const
            {
                return SerialiseMenuItemToJson(*this);
            }

            const std::string& MenuItemModel::Identifier() const
            {
                return m_identifier;
            }

            const std::string& MenuItemModel::Name() const
            {
                return m_name;
            }

            const std::string& MenuItemModel::Details() const
            {
                return m_details;
            }

            const std::string& MenuItemModel::Icon() const
            {
                return m_icon;
            }
            
            IMenuOption& MenuItemModel::MenuOption()
            {
                return *m_pOption;
            }
        }
    }
}
