// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "RepositoryModel.h"
#include "TweetModel.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class TweetRepository : public Repository::IRepositoryModel<TweetModel*>, private Eegeo::NonCopyable
            {
                typedef TweetModel* TModel;
                
                Repository::RepositoryModel<TModel> m_repository;
                
            public:
                ~TweetRepository()
                {
                    while(m_repository.GetItemCount() > 0)
                    {
                        TweetModel* tweetModel = m_repository.GetItemAtIndex(0);
                        m_repository.RemoveItem(tweetModel);
                    }
                }
                
                void AddItem(const TModel& item)
                {
                    m_repository.AddItem(item);
                }
                
                void RemoveItem(const TModel& item)
                {
                    m_repository.RemoveItem(item);
                    Eegeo_DELETE item;
                }
                
                size_t GetItemCount() const
                {
                    return m_repository.GetItemCount();
                }
                
                TModel GetItemAtIndex(size_t index)
                {
                    return m_repository.GetItemAtIndex(index);
                }
                
                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
                {
                    m_repository.InsertItemAddedCallback(callback);
                }
                
                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
                {
                    m_repository.RemoveItemAddedCallback(callback);
                }
                
                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
                {
                    m_repository.InsertItemRemovedCallback(callback);
                }
                
                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
                {
                    m_repository.RemoveItemRemovedCallback(callback);
                }
            };
        }
    }
}
