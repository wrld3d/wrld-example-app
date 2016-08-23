// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "TagSearchModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        class TagSearchAddedMessage
        {
        private:
            View::TagSearchModel m_model;

        public:
            TagSearchAddedMessage(const TagSearch::View::TagSearchModel& item)
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
