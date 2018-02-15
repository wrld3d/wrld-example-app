// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            struct QueryData
            {
                
            public:
                QueryData(const std::string& query,
                          const std::string& indoorId,
                          const std::string& mapscene,
                          const bool& hasQuery,
                          const bool& hasIndoorId,
                          const bool& hasMapscene,
                          const bool& parsedData)
                : m_query(query)
                , m_indoorId(indoorId)
                , m_mapscene(mapscene)
                , m_hasQuery(hasQuery)
                , m_hasIndoorId(hasIndoorId)
                , m_hasMapscene(hasMapscene)
                , m_parsedData(parsedData)
                {
                    
                }
                
                std::string GetQuery() const { return m_query; }
                std::string GetIndoorId() const { return m_indoorId; }
                std::string GetMapscene() const { return m_mapscene; }
                bool HasQuery() const { return m_hasQuery; }
                bool HasIndoorId() const { return m_hasIndoorId; }
                bool HasMapscene() const { return m_hasMapscene; }
                bool DidParseData() const { return m_parsedData; }
                
            private:
                std::string m_query;
                std::string m_indoorId;
                std::string m_mapscene;
                bool m_hasQuery;
                bool m_hasIndoorId;
                bool m_hasMapscene;
                bool m_parsedData;
            };
        }
    }
}
