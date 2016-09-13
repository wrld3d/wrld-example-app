// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "TagSearchModel.h"
#include "ITagSearchRepository.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class TagSearchRepositoryObserver : private Eegeo::NonCopyable
            {             
            private:
                const std::shared_ptr<TagSearch::View::ITagSearchRepository> m_repository;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<TagSearchRepositoryObserver, TagSearch::View::TagSearchModel> m_addedCallback;
                Eegeo::Helpers::TCallback1<TagSearchRepositoryObserver, TagSearch::View::TagSearchModel> m_removedCallback;

                void HandleTagSearchAdded(TagSearch::View::TagSearchModel& item);
                void HandleTagSearchRemoved(TagSearch::View::TagSearchModel& item);

            public:
                TagSearchRepositoryObserver(
                                            const std::shared_ptr<TagSearch::View::ITagSearchRepository>& tagSearchRepository,
                                            const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~TagSearchRepositoryObserver();
            };
        }
    }
}
