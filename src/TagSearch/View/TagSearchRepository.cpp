// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchRepository.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
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
            
            std::string GetTagSearchNameByQuery(const std::string& query)
            {
                if (query.length() == 0)
                {
                    return "Around Me";
                }
                
                std::string tagName = query;
                
                tagName[0] = toupper(query[0]);
                
                for (int i = 1; i < query.length(); ++i)
                {
                    if (query[i] == '_')
                    {
                        tagName[i] = ' ';
                    }
                    else if (query[i-1] == '_')
                    {
                        tagName[i] = toupper(query[i]);
                    }
                }
                
                return tagName;
            }

            std::string GetPresentationStringForQuery(ITagSearchRepository& tagSearchRepository, const Search::SdkModel::SearchQuery& query)
            {
                if(query.IsTag())
                {
                    std::string tagName;
                    const bool foundName = tagSearchRepository.TryGetTagSearchNameByQuery(query.Query(), tagName);
                    if (!foundName)
                    {
                        tagName = GetTagSearchNameByQuery(query.Query());
                    }
                    
                    return tagName;
                }
                else
                {
                    return query.Query();
                }
            }

            void TagSearchRepository::ForceRefresh()
            {
                // HACK: Forcably remove and add all items to ensure the view is updated correctly
                // This is due to the view not being given initial state on construction
                size_t itemCount = GetItemCount();
                std::vector<TagSearch::View::TagSearchModel> tags;
                for(size_t i = 0; i < itemCount; ++i)
                {
                    View::TagSearchModel tag = GetItemAtIndex(i);
                    tags.push_back(tag);
                }

                for(size_t i = 0; i < itemCount; ++i)
                {
                    View::TagSearchModel tag = tags.at(i);
                    RemoveItem(tag);
                    AddItem(tag);
                }
            }
        }
    }
}
