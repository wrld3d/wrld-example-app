// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Types.h"
#include "RepositoryModel.h"
#include "SearchResultModel.h"
#include <map>

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchTag
            {
            private:
                std::string m_tag;
                std::string m_readableTag;
                TagIconKey m_iconKey;

            public:
                SearchTag(const std::string& tag,
                          const std::string& readableTag,
                          const TagIconKey& iconKey)

                : m_tag(tag)
                , m_readableTag(readableTag)
                , m_iconKey(iconKey)
                {
                }
                
                const std::string& GetTag() const { return m_tag; }
                const std::string& GetReadableTag() const { return m_readableTag; }
                const TagIconKey& GetIconKey() const { return m_iconKey; }
            };
            
            inline bool operator==(const SearchTag& lhs, const SearchTag& rhs)
            {
                return lhs.GetTag() == rhs.GetTag();
            }
            inline bool operator!=(const SearchTag& lhs, const SearchTag& rhs)
            {
                return !operator==(lhs,rhs);
            }
            inline bool operator< (const SearchTag& lhs, const SearchTag& rhs)
            {
                return lhs.GetTag() < rhs.GetTag();
            }
            inline bool operator> (const SearchTag& lhs, const SearchTag& rhs)
            {
                return  operator< (rhs,lhs);
            }
            inline bool operator<=(const SearchTag& lhs, const SearchTag& rhs)
            {
                return !operator> (lhs,rhs);
            }
            inline bool operator>=(const SearchTag& lhs, const SearchTag& rhs)
            {
                return !operator< (lhs,rhs);
            }

            class SearchTagRepository : public Repository::IRepositoryModel<SearchTag>
            {
            private:
                std::string m_defaultReadableTag;
                TagIconKey m_defaultIconKey;
                Repository::RepositoryModel<SearchTag> m_repository;
                
            public:
                void AddItem(const SearchTag& item) override
                {
                    m_repository.AddItem(item);
                }
                
                void RemoveItem(const SearchTag& item) override
                {
                    m_repository.RemoveItem(item);
                }
                
                size_t GetItemCount() const override
                {
                    return m_repository.GetItemCount();
                }
                
                SearchTag GetItemAtIndex(size_t index) override
                {
                    return m_repository.GetItemAtIndex(index);
                }
                
                const SearchTag GetItemAtIndexConst(size_t index) const
                {
                    return m_repository.GetItemAtIndexConst(index);
                }
                
                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<SearchTag>& callback) override
                {
                    m_repository.InsertItemAddedCallback(callback);
                }
                
                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<SearchTag>& callback) override
                {
                    m_repository.RemoveItemAddedCallback(callback);
                }
                
                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<SearchTag>& callback) override
                {
                    m_repository.InsertItemRemovedCallback(callback);
                }
                
                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<SearchTag>& callback) override
                {
                    m_repository.RemoveItemRemovedCallback(callback);
                }
                
                const std::string& GetDefaultReadableTag() const { return m_defaultReadableTag; }
                
                const TagIconKey& GetDefaultIconKey() const { return m_defaultIconKey; }
                
                void SetDefaultReadableTag(const std::string& defaultReadableTag)
                {
                    m_defaultReadableTag = defaultReadableTag;
                }
                
                void SetDefaultIconKey(const TagIconKey& defaultIconKey)
                {
                    m_defaultIconKey = defaultIconKey;
                }
                
                bool HasTag(const std::string& tagName) const
                {
                    for (size_t i = 0; i<GetItemCount(); ++i)
                    {
                        const auto& t = GetItemAtIndexConst(i);
                        if (t.GetTag() == tagName)
                        {
                            return true;
                        }
                    }
                    return false;
                }
            };
        }
    }
}
