// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchRepository.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            TagSearchRepository::TagSearchRepository(const std::vector<TagSearch::View::TagSearchModel>& tagSearchModels)
            {
                for(int i = 0; i < tagSearchModels.size(); ++i)
                {
                    AddItem(tagSearchModels[i]);
                }
            }

            bool TagSearchRepository::TryGetTagSearchNameByQuery(const std::string& query, std::string& out_name)
            {
                const auto count = m_repository.GetItemCount();

                for(size_t i = 0; i < count; ++i)
                {
                    const auto& model = m_repository.GetItemAtIndex(i);
                    if(model.SearchTag() == query)
                    {
                        out_name = model.Name();
                        return true;
                    }
                }

                return false;
            }

            void TagSearchRepository::AddItem(const TagSearchModel& item)
            {
                m_repository.AddItem(item);
            }

            void TagSearchRepository::RemoveItem(const TagSearchModel& item)
            {
                m_repository.RemoveItem(item);
            }

            size_t TagSearchRepository::GetItemCount() const
            {
                return m_repository.GetItemCount();
            }

            TagSearchModel TagSearchRepository::GetItemAtIndex(size_t index)
            {
                return m_repository.GetItemAtIndex(index);
            }

            void TagSearchRepository::InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback)
            {
                m_repository.InsertItemAddedCallback(callback);
            }

            void TagSearchRepository::RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback)
            {
                m_repository.RemoveItemAddedCallback(callback);
            }

            void TagSearchRepository::InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback)
            {
                m_repository.InsertItemRemovedCallback(callback);
            }

            void TagSearchRepository::RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TagSearchModel>& callback)
            {
                m_repository.RemoveItemRemovedCallback(callback);
            }

            std::string GetPresentationStringForQuery(ITagSearchRepository& tagSearchRepository, const Search::SdkModel::SearchQuery& query)
            {
                if(query.IsTag())
                {
                    std::string tagName;
                    const bool foundName = tagSearchRepository.TryGetTagSearchNameByQuery(query.Query(), tagName);
                    Eegeo_ASSERT(foundName, "Unable to find name for tag query %s.\n", query.Query().c_str());
                    return tagName;
                }
                else
                {
                    return query.Query();
                }
            }
        }
    }
}
