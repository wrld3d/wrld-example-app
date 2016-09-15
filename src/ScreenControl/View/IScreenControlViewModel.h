// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IIdentity.h"
#include "RepositoryModel.h"

#include <vector>

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            class IScreenControlViewModel : public virtual Eegeo::Helpers::IIdentity
            {
            public:
                virtual ~IScreenControlViewModel() { }

                virtual void AddToScreen() = 0;

                virtual void RemoveFromScreen() = 0;

                virtual void UpdateOnScreenState(float onScreenState) = 0;

                virtual void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback) = 0;

                virtual void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback) = 0;

                virtual bool IsFullyOffScreen() const = 0;

                virtual bool IsFullyOnScreen() const = 0;

                virtual float OnScreenState() const = 0;
                
                virtual bool IsAddedToScreen() const = 0;
            };
            
            class TReactors : public Repository::IRepositoryModel<ScreenControl::View::IScreenControlViewModel*>
            {
            private:
                typedef ScreenControl::View::IScreenControlViewModel* TModel;
                Repository::RepositoryModel<TModel> m_repository;
                
            public:
                void AddItem(const TModel& item) override
                {
                    m_repository.AddItem(item);
                }
                
                void RemoveItem(const TModel& item) override
                {
                    m_repository.RemoveItem(item);
                }
                
                size_t GetItemCount() const override
                {
                    return m_repository.GetItemCount();
                }
                
                TModel GetItemAtIndex(size_t index) override
                {
                    return m_repository.GetItemAtIndex(index);
                }
                
                const TModel GetItemAtIndexConst(size_t index) const
                {
                    return m_repository.GetItemAtIndexConst(index);
                }
                
                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback) override
                {
                    m_repository.InsertItemAddedCallback(callback);
                }
                
                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback) override
                {
                    m_repository.RemoveItemAddedCallback(callback);
                }
                
                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback) override
                {
                    m_repository.InsertItemRemovedCallback(callback);
                }
                
                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback) override
                {
                    m_repository.RemoveItemRemovedCallback(callback);
                }
            };
        }
    }
}
