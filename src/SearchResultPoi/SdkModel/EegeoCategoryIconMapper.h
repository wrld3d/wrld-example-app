// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICategoryIconMapper.h"
#include <map>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoCategoryIconMapper : public SearchResultPoi::SdkModel::ICategoryIconMapper, private Eegeo::NonCopyable
                {
                    //TODO: Optimise out values into separate vector
                    std::map<std::string, std::string> m_tagIconMapping;

                    const std::string m_defaultCategory;

                public:
                    EegeoCategoryIconMapper();

                    ~EegeoCategoryIconMapper();

                    std::string GetIconForCategories(const std::vector<std::string>& tags) const;
                };
            }
        }
    }
}
