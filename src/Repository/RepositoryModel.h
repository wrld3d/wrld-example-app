// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ObservableVector.h"
#include "IRepositoryModel.h"

namespace ExampleApp
{
    namespace Repository
    {
        template<typename TItem>
        class RepositoryModel : public IRepositoryModel<TItem>
        {
        protected:
            Eegeo::Helpers::ObservableVector<TItem> m_items;

        public:
            RepositoryModel() {}

            void AddItem(const TItem& item)
            {
                TItem i = item;
                m_items.AddItem(i);
            }

            void RemoveItem(const TItem& item)
            {
                TItem i = item;
                m_items.RemoveItem(i);
            }

            size_t GetItemCount() const
            {
                return m_items.size();
            }

            TItem GetItemAtIndex(size_t index)
            {
                return m_items.at(index);
            }

            void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TItem>& callback)
            {
                m_items.AddItemAddedCallback(callback);
            }

            void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TItem>& callback)
            {
                m_items.RemoveItemAddedCallback(callback);
            }

            void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TItem>& callback)
            {
                m_items.AddItemRemovedCallback(callback);
            }

            void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TItem>& callback)
            {
                m_items.RemoveItemRemovedCallback(callback);
            }
        };
    }
}
