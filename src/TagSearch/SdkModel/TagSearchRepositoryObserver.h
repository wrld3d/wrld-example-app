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
                TagSearch::View::ITagSearchRepository& m_repository;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<TagSearchRepositoryObserver, TagSearch::View::TagSearchModel> m_addedCallback;
                Eegeo::Helpers::TCallback1<TagSearchRepositoryObserver, TagSearch::View::TagSearchModel> m_removedCallback;

                void HandleTagSearchAdded(TagSearch::View::TagSearchModel& item);
                void HandleTagSearchRemoved(TagSearch::View::TagSearchModel& item);

            public:
                TagSearchRepositoryObserver(
                        TagSearch::View::ITagSearchRepository& tagSearchRepository,
                        ExampleAppMessaging::TMessageBus& messageBus);

                ~TagSearchRepositoryObserver();
            };
        }
    }
}
