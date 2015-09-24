// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Web.h"
#include "IYelpCategoryMapper.h"
#include "WebLoadRequestCompletionCallback.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpCategoryMapper : public IYelpCategoryMapper, private Eegeo::NonCopyable
                {
                    typedef std::map<std::string, std::string>::iterator mapIt;
                    
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    std::map<std::string, std::string> m_yelpLeafCategoryToYelpFoundationCategoryMap;
                    std::map<std::string, std::string> m_yelpToApplicationCategoryMap;
                    std::string m_defaultCategory;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<YelpCategoryMapper> m_yelpTaxonomyRequestCompletedCallback;
                    bool m_isDownloadingTaxonomy;
                    bool m_hasDownloadedTaxonomy;
                    
                    void DispatchTaxonomyRequest();
                    void OnYelpTaxonomyRequestCompleted(Eegeo::Web::IWebLoadRequest& webLoadRequest);
                    void ParseYelpCategoryTaxonomy(const std::string& serializedTaxonomyJson);
                    
                public:
                    YelpCategoryMapper(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                       const std::map<std::string, std::string>& yelpToApplicationCategoryMap,
                                       const std::string& defaultCategory);
                    
                    bool TryGetBestMatchingApplicationCategoryForYelpCategories(const std::vector<std::string>& yelpCategories,
                                                                                std::string& out_bestMatchedAppCategory);
                };
            }
        }
    }
}
