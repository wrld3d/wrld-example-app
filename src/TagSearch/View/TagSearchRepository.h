// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "TagSearch.h"
#include "ITagSearchRepository.h"
#include "TagSearchModel.h"
#include "Types.h"
#include "RepositoryModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchRepository : public ITagSearchRepository, private Eegeo::NonCopyable
            {
                Repository::RepositoryModel<TagSearchModel> m_repository;

            public:
                void AddItem(const TagSearchModel& item) override;
                void RemoveItem(const TagSearchModel& item) override;

                size_t GetItemCount() const override;
                TagSearchModel GetItemAtIndex(size_t index) override;

                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback) override;
                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback) override;
                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback) override;
                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback) override;

                bool TryGetTagSearchNameByQuery(const std::string& query, std::string& out_name) override;

                void ForceRefresh() override;
            };
        }
    }
}
