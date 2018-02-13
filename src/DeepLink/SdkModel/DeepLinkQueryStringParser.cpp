// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkQueryStringParser.h"
#include "StringHelpers.h"

namespace
{
    std::string DEFAULT_INDOOR_ID = "";
    
}

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkQueryStringParser::DeepLinkQueryStringParser()
            : m_hasMapScene(false)
            , m_hasIndoorId(false)
            , m_hasValidQueryString(false)
            , m_mapsceneString("")
            , m_indoorId("")
            {
            }
            
            void DeepLinkQueryStringParser::ParseData(const std::string& query)
            {
                std::stringstream ssquery(query);
                std::string segment;
                
                while(std::getline(ssquery, segment, '&'))
                {
                    if(segment.find("indoor_id") == 0)
                    {
                        m_indoorId = segment.substr(segment.find("=") + 1);
                        m_hasIndoorId = true;
                        m_hasValidQueryString = true;
                    }
                    
                    if(segment.find("mapscene") == 0)
                    {
                        m_mapsceneString = segment.substr(segment.find("=") + 1);
                        m_hasMapScene = true;
                        m_hasValidQueryString = true;
                    }
                }
            }
            
            AppInterface::UrlData DeepLinkQueryStringParser::GetSearchData(const AppInterface::UrlData& data)
            {
                AppInterface::UrlData searchData = data;
                std::string path = searchData.path;
                path.append("/" + m_indoorId);
                searchData.path = path.c_str();
                
                return searchData;
            }
            
            AppInterface::UrlData DeepLinkQueryStringParser::GetMapsceneData(const AppInterface::UrlData& data)
            {
                AppInterface::UrlData mapsceneData = data;
                mapsceneData.host = "mapscene";
                std::string path = "/" + m_mapsceneString;
                mapsceneData.path = path.c_str();
                
                return mapsceneData;
            }
            
            bool DeepLinkQueryStringParser::HasIndoorId()
            {
                return m_hasIndoorId;
            }
            
            bool DeepLinkQueryStringParser::HasMapScene()
            {
                return m_hasMapScene;
            }
            
            bool DeepLinkQueryStringParser::HasValidQueryString()
            {
                return m_hasValidQueryString;
            }
        }
    }
}
