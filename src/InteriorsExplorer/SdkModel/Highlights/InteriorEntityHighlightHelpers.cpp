// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorEntityHighlightHelpers.h"
#include "SearchResultModel.h"
#include "document.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                std::vector<std::string> GetEntityIdsFromJsonArray(const rapidjson::Value& jsonArray)
                {
                    assert(jsonArray.IsArray());
                    std::vector<std::string> entities;
                    
                    for (int i  = 0; i < jsonArray.Size(); i++)
                    {
                        assert(jsonArray[i].IsString());
                        entities.push_back(jsonArray[i].GetString());
                    }
                    
                    return entities;
                }
                
                std::vector<std::string> GetEntityIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                {
                    return GetEntityIdsFromSearchResultJson(selectedSearchResult.GetJsonData());
                }

                std::vector<std::string> GetEntityIdsFromSearchResultJson(const std::string& jsonData)
                {
                    rapidjson::Document json;
                    std::vector<std::string> entities;

                    if (!json.Parse<0>(jsonData.c_str()).HasParseError())
                    {
                        if(json.HasMember("highlight"))
                        {
                            const rapidjson::Value& areaHighlight = json["highlight"];
                            if(areaHighlight.IsString())
                            {
                                entities.push_back(areaHighlight.GetString());
                            }
                            else
                            {
                                std::vector<std::string> areaHighlights = GetEntityIdsFromJsonArray(areaHighlight);
                                entities.insert(std::end(entities), std::begin(areaHighlights), std::end(areaHighlights));
                            }
                        }
                        
                        if(json.HasMember("entity_highlight")  )
                        {
                            const rapidjson::Value& entityHighlight = json["entity_highlight"];
                            if(entityHighlight.IsString())
                            {
                                entities.push_back(entityHighlight.GetString());
                            }
                            else
                            {
                                std::vector<std::string> entityHighlights = GetEntityIdsFromJsonArray(entityHighlight);
                                entities.insert(std::end(entities), std::begin(entityHighlights), std::end(entityHighlights));
                            }
                        }
                    }
                    
                    return entities;
                }

                float GetBorderThicknessFromValue(rapidjson::Value& value) {
                    const auto defaultHighlightBorderThickness = Eegeo::Resources::Interiors::Highlights::DefaultInteriorHighlightBorderThickness;

                    if (value.IsNumber()) {
                        return static_cast<float>(value.GetDouble());
                    }
                    else {
                        return defaultHighlightBorderThickness;
                    }
                }

                std::vector<float> GetHighlightBorderThicknessFromSearchResultJson(const std::string& jsonData)
                {
                    rapidjson::Document json;
                    std::vector<float> borderThickness;

                    const auto highlightBorderThicknessTag = "highlight_border_thickness";
                    const auto entityHighlightBorderThicknessTag = "entity_highlight_border_thickness";

                    const auto defaultHighlightBorderThickness = Eegeo::Resources::Interiors::Highlights::DefaultInteriorHighlightBorderThickness;

                    if (!json.Parse<0>(jsonData.c_str()).HasParseError() )
                    {
                        if(json.HasMember("highlight"))
                        {
                            borderThickness.push_back( json.HasMember(highlightBorderThicknessTag) ? GetBorderThicknessFromValue(json[highlightBorderThicknessTag]): defaultHighlightBorderThickness );
                        }

                        if(json.HasMember("entity_highlight"))
                        {
                            borderThickness.push_back( json.HasMember(entityHighlightBorderThicknessTag) ? GetBorderThicknessFromValue(json[entityHighlightBorderThicknessTag]): defaultHighlightBorderThickness );
                        }
                    }

                    if (borderThickness.size() == 0){
                        borderThickness.push_back(defaultHighlightBorderThickness);
                    }

                    return borderThickness;
                }

                std::vector<float> GetHighlightBorderThicknessFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                {
                    return GetHighlightBorderThicknessFromSearchResultJson(selectedSearchResult.GetJsonData());
                }
            }
        }
    }
}
