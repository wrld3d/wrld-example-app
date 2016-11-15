// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuSectionViewModel.h"

#include <string>
#include "CallbackCollection.h"
#include "Types.h"
#include "Menu.h"


namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuSectionViewModel : public IMenuSectionViewModel, private Eegeo::NonCopyable
            {
            public:

                MenuSectionViewModel(const std::string& name, const std::string& icon, IMenuModel& menuModel, bool isExpandable);
                
                IMenuModel& GetModel() const
                {
                    return m_menuModel;
                }
                
                const std::string& Name() const
                {
                    return m_name;
                }

                const std::string& Icon() const
                {
                    return m_icon;
                }

                std::string Details() const
                {
                    return m_details;
                }

                std::string SerializeJson() const;

                size_t Size() const;

                size_t GetTotalItemCount() const;

                MenuItemModel GetItemAtIndex(int index) const;

                bool IsExpanded() const
                {
                    return m_isExpandable ? m_expanded : true;
                }
                
                bool IsExpandable() const
                {
                    return m_isExpandable;
                }

                void Expand();
                void Contract();
                
                void InsertExpandedChangedCallback(Eegeo::Helpers::ICallback2<IMenuSectionViewModel&, bool>& callback);
                void RemoveExpandedChangedCallback(Eegeo::Helpers::ICallback2<IMenuSectionViewModel&, bool>& callback);

            private:

                std::string m_name;
                std::string m_icon;
                std::string m_details;
                IMenuModel& m_menuModel;
                const bool m_isExpandable;
                bool m_expanded;
                
                Eegeo::Helpers::CallbackCollection2<IMenuSectionViewModel&, bool> m_expandedChangedCallbacks;
            };
        }
    }
}
