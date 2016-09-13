// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Web.h"
#include "IYelpCategoryToTagMapper.h"
#include "WebLoadRequestCompletionCallback.h"
#include "YelpSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpCategoryToTagMapper : public IYelpCategoryToTagMapper, private Eegeo::NonCopyable
                {
                    typedef std::map<std::string, std::string>::iterator mapIt;
                    
                    std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory> m_webRequestFactory;
                    std::map<std::string, std::string> m_yelpLeafCategoryToYelpFoundationCategoryMap;
                    const std::shared_ptr<SearchConstants::YelpCategoryMappingData> m_yelpMappingData;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<YelpCategoryToTagMapper> m_yelpTaxonomyRequestCompletedCallback;
                    bool m_isDownloadingTaxonomy;
                    bool m_hasDownloadedTaxonomy;
                    
                    void DispatchTaxonomyRequest();
                    void OnYelpTaxonomyRequestCompleted(Eegeo::Web::IWebResponse& webResponse);
                    void ParseYelpCategoryTaxonomy(const std::string& serializedTaxonomyJson);
                    
                public:
                    YelpCategoryToTagMapper(const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webRequestFactory,
                                            const std::shared_ptr<SearchConstants::YelpCategoryMappingData>& yelpMappingData);
                    
                    bool TryGetBestMatchingTagForYelpCategories(const std::vector<std::string>& yelpCategories,
                            std::string& out_bestMatchedAppTag);
                };
            }
        }
    }
}
