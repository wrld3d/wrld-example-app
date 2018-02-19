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
            
            QueryData DeepLinkQueryStringParser::ParseData(const AppInterface::UrlData& data) const
            {
                std::stringstream ssquery;
                if(data.query != NULL)
                {
                    ssquery.str(data.query);
                }
                std::string segment;
                
                std::string indoorId = "";
                std::string mapscene = "";
                std::string queryString = "";
                bool hasIndoorId = false;
                bool hasMapscene = false;
                bool hasQuery = false;
                bool parsedData = false;
                    
                while(std::getline(ssquery, segment, '&'))
                {
                    if(segment.find("indoor_id") == 0)
                    {
                        indoorId = segment.substr(segment.find("=") + 1);
                        hasIndoorId = true;
                    }
                    
                    if(segment.find("mapscene") == 0)
                    {
                        mapscene = segment.substr(segment.find("=") + 1);
                        hasMapscene = true;
                    }
                    
                    if(segment.find("query") == 0)
                    {
                        queryString = segment.substr(segment.find("=") + 1);
                        hasQuery = true;
                    }
                    parsedData = true;
                }
                
                return QueryData(queryString,
                                 indoorId,
                                 mapscene,
                                 hasQuery,
                                 hasIndoorId,
                                 hasMapscene,
                                 parsedData);
            }

        }
    }
}
