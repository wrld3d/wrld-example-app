// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchMenuOption.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"
#include "TagSearchSelectedMessage.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            TagSearchMenuOption::TagSearchMenuOption(TagSearchModel model,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_model(model)
                , m_messageBus(messageBus)
            {
            }

            TagSearchMenuOption::~TagSearchMenuOption()
            {

            }

            void TagSearchMenuOption::Select()
            {
                m_messageBus.Publish(TagSearchSelectedMessage(m_model.SearchTag(), m_model.Interior()));
            }
        }
    }
}
