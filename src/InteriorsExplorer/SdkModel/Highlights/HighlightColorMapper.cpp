#include "HighlightColorMapper.h"
#include "ISearchResultRepository.h"
//#include "document.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                Eegeo::v4 HighlightColorMapper::GetColorFromValue(rapidjson::Value& value) const {
                    if (value.IsArray()) {
                        Eegeo::v4 highlightColor = m_defaultColor;

                        if (value.Size() == 4) {
                            highlightColor.Set(value[0].GetDouble() / 255.0,
                                               value[1].GetDouble() / 255.0,
                                               value[2].GetDouble() / 255.0,
                                               value[3].GetDouble() / 255.0);
                        }

                        return highlightColor;
                    }
                    else {
                        return m_defaultColor;
                    }
                }
                
                Eegeo::v4 HighlightColorMapper::GetColor(const Search::SdkModel::SearchResultModel& result, const std::string highlightColorData) const
                {
                    rapidjson::Document json;
                    Eegeo::v4 highlightColor = m_defaultColor;
                    
                    if (!json.Parse<0>(result.GetJsonData().c_str()).HasParseError() && json.HasMember(highlightColorData.c_str()))
                    {
                        highlightColor = GetColorFromValue(json[highlightColorData.c_str()]);
                    }
                    
                    return highlightColor;
                }
                
                std::vector<Eegeo::v4> HighlightColorMapper::GetColors(const Search::SdkModel::SearchResultModel& result) const
                {
                    return GetColorsFromJson(result.GetJsonData());
                }

                std::vector<Eegeo::v4> HighlightColorMapper::GetColorsFromJson(const std::string& jsonData) const
                {
                    rapidjson::Document json;
                    
                    std::vector<Eegeo::v4>highlightColors;
                    
                    auto highlightColorTag = "highlight_color";
                    auto entityHighlightColorTag = "entity_highlight_color";

                    if (!json.Parse<0>(jsonData.c_str()).HasParseError() )
                    {

                        if(json.HasMember("highlight"))
                        {
                            highlightColors.push_back( json.HasMember(highlightColorTag) ? GetColorFromValue(json[highlightColorTag]): m_defaultColor );
                        }
                        
                        if(json.HasMember("entity_highlight"))
                        {
                            highlightColors.push_back( json.HasMember(entityHighlightColorTag) ? GetColorFromValue(json[entityHighlightColorTag]): m_defaultColor );
                        }
                        
                    }
                    
                    if (highlightColors.size() == 0){
                        highlightColors.push_back(m_defaultColor);
                    }
                    
                    return highlightColors;
                }
            }
        }
    }
}
