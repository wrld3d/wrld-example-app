// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpCategoryToTagMapper.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "document.h"

namespace
{
    void RecursivelyMapYelpCategoryTaxonomySubHierarchyToFoundationCategory(const rapidjson::Value& subHierarchyRoot,
                                                                            const std::string& rootYelpCategoryName,
                                                                            const std::map<std::string, std::string>& foundationCategoriesMapping,
                                                                            std::map<std::string, std::string>& outputMapping)
    {
        for(size_t i = 0; i < subHierarchyRoot.Size(); ++i)
        {
            unsigned int index = static_cast<unsigned int>(i);
            const rapidjson::Value& entry = subHierarchyRoot[index];
            std::string category(entry["alias"].GetString());
            const rapidjson::Value& subTree(entry["category"]);
            const bool isMyCategoryRoot(foundationCategoriesMapping.find(category) != foundationCategoriesMapping.end());
            std::string nextRootCategory = isMyCategoryRoot ? category : rootYelpCategoryName;
            outputMapping[category] = nextRootCategory;
            RecursivelyMapYelpCategoryTaxonomySubHierarchyToFoundationCategory(subTree,
                                                                               nextRootCategory,
                                                                               foundationCategoriesMapping,
                                                                               outputMapping);
        }
    }
}

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                const char* YelpCategoryTaxonomyUrl("https://cdn1.eegeo.com/search/yelp/v2/en/category.json.gz");
                
                YelpCategoryToTagMapper::YelpCategoryToTagMapper(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                       const std::map<std::string, std::string>& yelpToApplicationTagMap,
                                                       const std::string& defaultTag)
                : m_webRequestFactory(webRequestFactory)
                , m_yelpToApplicationTagMap(yelpToApplicationTagMap)
                , m_defaultTag(defaultTag)
                , m_yelpTaxonomyRequestCompletedCallback(this, &YelpCategoryToTagMapper::OnYelpTaxonomyRequestCompleted)
                , m_isDownloadingTaxonomy(false)
                , m_hasDownloadedTaxonomy(false)
                {
                    DispatchTaxonomyRequest();
                }
                
                bool YelpCategoryToTagMapper::TryGetBestMatchingTagForYelpCategories(const std::vector<std::string>& yelpCategories,
                        std::string& out_bestMatchedAppTag)
                {
                    if(!m_hasDownloadedTaxonomy)
                    {
                        if(!m_isDownloadingTaxonomy)
                        {
                            // Somehow we failed to download the taxonomy at start-up, we didn't have it cached, and we are not currently
                            // downloading it. Possibly we have never downloaded it before, and the download timed out? If so, kick off the
                            // download again, and fall back to the default tag in the meantime.
                            DispatchTaxonomyRequest();
                        }
                    }
                    else
                    {
                        /*
                         For the listed categories in sequence, map the Yelp result leaf category back it its foundation category (its
                         root in the taxonomy) and then map this root category from Yelp taxonomy to application tag name.
                         
                         Use default tag if no match.
                         */
                        for(std::vector<std::string>::const_iterator it = yelpCategories.begin(); it != yelpCategories.end(); ++ it)
                        {
                            const std::string& queryYelpCategory(*it);
                            const mapIt yelpLeafToFoundationIt(m_yelpLeafCategoryToYelpFoundationCategoryMap.find(queryYelpCategory));
                            
                            if(yelpLeafToFoundationIt != m_yelpLeafCategoryToYelpFoundationCategoryMap.end())
                            {
                                const std::string& yelpFoundationCategory(yelpLeafToFoundationIt->second);
                                const mapIt yelpFoundationategoryToAppCategoryIt(m_yelpToApplicationTagMap.find(yelpFoundationCategory));
                                
                                if(yelpFoundationategoryToAppCategoryIt != m_yelpToApplicationTagMap.end())
                                {
                                    out_bestMatchedAppTag = yelpFoundationategoryToAppCategoryIt->second;
                                    return true;
                                }
                            }
                        }
                    }
                    
                    out_bestMatchedAppTag = m_defaultTag;
                    return false;
                }
                
                void YelpCategoryToTagMapper::DispatchTaxonomyRequest()
                {
                    Eegeo_ASSERT(!m_hasDownloadedTaxonomy);
                    m_isDownloadingTaxonomy = true;
                    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, YelpCategoryTaxonomyUrl, m_yelpTaxonomyRequestCompletedCallback)
                        .Build()->Load();
                }
                
                void YelpCategoryToTagMapper::OnYelpTaxonomyRequestCompleted(Eegeo::Web::IWebResponse& webResponse)
                {
                    Eegeo_ASSERT(m_isDownloadingTaxonomy);
                    m_isDownloadingTaxonomy = false;
                    
                    if(webResponse.IsSucceeded())
                    {
                        m_hasDownloadedTaxonomy = true;
                        const size_t resultSize = webResponse.GetBodyData().size();
                        const std::string serializedTaxonomyJson(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);
                        ParseYelpCategoryTaxonomy(serializedTaxonomyJson);
                    }
                }
                
                void YelpCategoryToTagMapper::ParseYelpCategoryTaxonomy(const std::string& serializedTaxonomyJson)
                {
                    rapidjson::Document document;
                    
                    if (!document.Parse<0>(serializedTaxonomyJson.c_str()).HasParseError())
                    {
                        size_t numFoundationCategories = document.Size();
                        
                        for(size_t i = 0; i < numFoundationCategories; ++i)
                        {
                            unsigned int index = static_cast<unsigned int>(i);
                            const rapidjson::Value& entry = document[index];
                            std::string foundationCategory(entry["alias"].GetString());
                            const rapidjson::Value& subTree(entry["category"]);
                            m_yelpLeafCategoryToYelpFoundationCategoryMap[foundationCategory] = foundationCategory;
                            RecursivelyMapYelpCategoryTaxonomySubHierarchyToFoundationCategory(subTree,
                                                                                               foundationCategory,
                                                                                               m_yelpToApplicationTagMap,
                                                                                               m_yelpLeafCategoryToYelpFoundationCategoryMap);
                        }
                    }
                }
            }
        }
    }
}
