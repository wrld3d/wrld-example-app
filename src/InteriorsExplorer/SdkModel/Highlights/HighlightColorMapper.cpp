#include "HighlightColorMapper.h"
#include "ISearchResultRepository.h"
#include "document.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                Eegeo::v4 HighlightColorMapper::GetColor(const Search::SdkModel::SearchResultModel& result, const std::string highlightColorData) const
                {
                    rapidjson::Document json;
                    Eegeo::v4 highlightColor = m_defaultColor;
                    
                    if (!json.Parse<0>(result.GetJsonData().c_str()).HasParseError() && json.HasMember(highlightColorData.c_str()))
                    {
                        const rapidjson::Value& entity_highlight_color = json[highlightColorData.c_str()];
                        assert(entity_highlight_color.IsArray());
                        
                        if (entity_highlight_color.Size() == 4)
                        {
                            highlightColor.Set(entity_highlight_color[0].GetDouble()/255.0,
                                               entity_highlight_color[1].GetDouble()/255.0,
                                               entity_highlight_color[2].GetDouble()/255.0,
                                               entity_highlight_color[3].GetDouble()/255.0);
                        }
                    }
                    return highlightColor;
                }
            }
        }
    }
}
