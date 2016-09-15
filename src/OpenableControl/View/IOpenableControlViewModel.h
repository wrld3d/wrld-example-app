// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IIdentity.h"
#include "RepositoryModel.h"
#include <vector>

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            class IOpenableControlViewModel : public virtual Eegeo::Helpers::IIdentity
            {
            public:
                virtual ~IOpenableControlViewModel() { }

                virtual bool HasReactorControl() const = 0;

                virtual bool TryAcquireReactorControl() = 0;

                virtual void ReleaseReactorControl() = 0;

                virtual bool Open(bool acquireReactor = true) = 0;

                virtual bool Close(bool releaseReactor = true) = 0;

                virtual void UpdateOpenState(float openState) = 0;

                virtual void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback) = 0;

                virtual void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback) = 0;

                virtual bool IsFullyOpen() const = 0;

                virtual bool IsFullyClosed() const = 0;

                virtual float OpenState() const = 0;
            };

            class TOpenables : public Repository::IRepositoryModel<OpenableControl::View::IOpenableControlViewModel*>
            {
            private:
                typedef OpenableControl::View::IOpenableControlViewModel* TModel;
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
