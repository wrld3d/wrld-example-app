// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            class CategorySearchSelectedMessageHandler : private Eegeo::NonCopyable
            {
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<CategorySearchSelectedMessageHandler, const CategorySearchSelectedMessage&> m_handlerBinding;

                void OnCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message);

            public:
                CategorySearchSelectedMessageHandler(
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~CategorySearchSelectedMessageHandler();
            };
        }
    }
}
