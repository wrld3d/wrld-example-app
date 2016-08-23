// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TagSearchRepositoryObserver.h"
#include "TagSearchAddedMessage.h"
#include "TagSearchRemovedMessage.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            TagSearchRepositoryObserver::TagSearchRepositoryObserver(
                    TagSearch::View::ITagSearchRepository& tagSearchRepository,
                    ExampleAppMessaging::TMessageBus& messageBus)
            : m_addedCallback(this, &TagSearchRepositoryObserver::HandleTagSearchAdded)
            , m_removedCallback(this, &TagSearchRepositoryObserver::HandleTagSearchRemoved)
            , m_repository(tagSearchRepository)
            , m_messageBus(messageBus)
            {
                m_repository.InsertItemAddedCallback(m_addedCallback);
                m_repository.InsertItemRemovedCallback(m_removedCallback);
            }

            TagSearchRepositoryObserver::~TagSearchRepositoryObserver()
            {
                m_repository.RemoveItemAddedCallback(m_addedCallback);
                m_repository.RemoveItemRemovedCallback(m_removedCallback);
            }

            void TagSearchRepositoryObserver::HandleTagSearchAdded(TagSearch::View::TagSearchModel& item)
            {
                m_messageBus.Publish(TagSearchAddedMessage(item));
            }

            void TagSearchRepositoryObserver::HandleTagSearchRemoved(TagSearch::View::TagSearchModel& item)
            {
                m_messageBus.Publish(TagSearchRemovedMessage(item));
            }
        }
    }
}
