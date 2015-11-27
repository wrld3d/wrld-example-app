// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourRepository.h"
#include "RepositoryModel.h"
#include "TourModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourRepository : public ITourRepository, private Eegeo::NonCopyable
            {
                typedef TourModel TModel;
                
                Repository::RepositoryModel<TModel> m_repository;
                
            public:
                void AddItem(const TModel& item)
                {
                    m_repository.AddItem(item);
                }
                
                void RemoveItem(const TModel& item)
                {
                    m_repository.RemoveItem(item);
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
                
                bool ContainsTourModelWithName(const std::string& name)
                {
                    size_t itemCount = m_repository.GetItemCount();
                    for(size_t i = 0; i < itemCount; i++)
                    {
                        TModel model = m_repository.GetItemAtIndex(i);
                        if(model.Name() == name)
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                TModel GetTourModelWithName(const std::string& name)
                {
                    size_t itemCount = m_repository.GetItemCount();
                    for(size_t i = 0; i < itemCount; i++)
                    {
                        TModel model = m_repository.GetItemAtIndex(i);
                        if(model.Name() == name)
                        {
                            return model;
                        }
                    }
                    
                    Eegeo_ASSERT(false, "Failed to find tour with name '%s'", name.c_str());
                    return TourModel::Empty();
                }
                
                bool ContainsTourModelWithTwitterBaseUserName(const std::string& name)
                {
                    size_t itemCount = m_repository.GetItemCount();
                    for(size_t i = 0; i < itemCount; i++)
                    {
                        TModel model = m_repository.GetItemAtIndex(i);
                        if(model.UsesTwitter() && model.TwitterBaseUserName() == name)
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                TModel GetTourModelWithTwitterBaseUserName(const std::string& name)
                {
                    size_t itemCount = m_repository.GetItemCount();
                    for(size_t i = 0; i < itemCount; i++)
                    {
                        TModel model = m_repository.GetItemAtIndex(i);
                        if(model.UsesTwitter() && model.TwitterBaseUserName() == name)
                        {
                            return model;
                        }
                    }
                    
                    Eegeo_ASSERT(false, "Failed to find tour with name '%s'", name.c_str());
                    return TourModel::Empty();
                }
            };
        }
    }
}
