// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoTagIconMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            EegeoTagIconMapper::EegeoTagIconMapper(const std::shared_ptr<Search::SdkModel::SearchTagRepository>& searchTags)
            {
                for(size_t i = 0; i<searchTags->GetItemCount(); ++i)
                {
                    const auto& t = searchTags->GetItemAtIndex(i);
                    Eegeo_ASSERT(m_tagToTagIconKeyMapping.find(t.GetTag()) == m_tagToTagIconKeyMapping.end(),
                                 "A mapping already exists for tag %s", t.GetTag().c_str());
                    
                    m_tagToTagIconKeyMapping.insert(std::make_pair(t.GetTag(), t.GetIconKey()));
                }
                
                m_defaultIconKey = searchTags->GetDefaultIconKey();
            }

            EegeoTagIconMapper::~EegeoTagIconMapper()
            {
                
            }

            ExampleApp::Search::SdkModel::TagIconKey EegeoTagIconMapper::GetIconKeyForTags(const std::vector<std::string>& tags) const
            {
                for (std::vector<std::string>::const_iterator tag = tags.begin();
                    tag != tags.end();
                    ++tag)
                {
                    std::map<std::string, std::string>::const_iterator result = m_tagToTagIconKeyMapping.find(*tag);

                    if (result != m_tagToTagIconKeyMapping.end())
                    {
                        return result->second;
                    }
                }

                return m_defaultIconKey;
            }
        }
    }
}
