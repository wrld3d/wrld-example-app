// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

namespace ExampleApp
{
    namespace Repository
    {
        template<typename TItem>
        class IRepositoryModel
        {
        public:
            virtual ~IRepositoryModel() { }

            virtual void AddItem(const TItem& item) = 0;

            virtual void RemoveItem(const TItem& item) = 0;

            virtual size_t GetItemCount() const = 0;

            virtual TItem GetItemAtIndex(size_t index) = 0;

            virtual void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TItem>& callback) = 0;

            virtual void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TItem>& callback) = 0;

            virtual void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TItem>& callback) = 0;

            virtual void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TItem>& callback) = 0;
        };
    }
}
