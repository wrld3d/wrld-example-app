// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "TagSearchModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        class TagSearchRemovedMessage
        {
        private:
            View::TagSearchModel m_model;

        public:
            TagSearchRemovedMessage(const TagSearch::View::TagSearchModel& item)
            : m_model(item)
            {

            }

            const View::TagSearchModel& Model() const
            {
                return m_model;
            }
        };
    }
}
