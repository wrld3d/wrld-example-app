// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuModel.h"
#include "RepositoryModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuModel : public IMenuModel, private Eegeo::NonCopyable
            {
                Repository::RepositoryModel<MenuItemModel> m_repository;

            public:
                void AddItem(const MenuItemModel& item) override
                {
                    m_repository.AddItem(item);
                }

                void RemoveItem(const MenuItemModel& item) override
                {
                    m_repository.RemoveItem(item);
                }

                size_t GetItemCount() const override
                {
                    return m_repository.GetItemCount();
                }

                MenuItemModel GetItemAtIndex(size_t index) override
                {
                    return m_repository.GetItemAtIndex(index);
                }

                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<MenuItemModel>& callback) override
                {
                    m_repository.InsertItemAddedCallback(callback);
                }

                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<MenuItemModel>& callback) override
                {
                    m_repository.RemoveItemAddedCallback(callback);
                }

                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<MenuItemModel>& callback) override
                {
                    m_repository.InsertItemRemovedCallback(callback);
                }

                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<MenuItemModel>& callback) override
                {
                    m_repository.RemoveItemRemovedCallback(callback);
                }
            };
        }
    }
}
