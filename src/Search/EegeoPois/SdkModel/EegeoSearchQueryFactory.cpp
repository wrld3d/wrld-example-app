// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchQuery.h"
#include "EegeoInteriorSearchQuery.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchQueryFactory::EegeoSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                 Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                 const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 const std::string& serviceUrl,
							         const std::string& apiKey)
                : m_webRequestFactory(webRequestFactory)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_urlEncoder(urlEncoder)
                , m_serviceUrl(serviceUrl)
                , m_apiKey(apiKey)
                {
                    
                }
                
                EegeoSearchQueryFactory::~EegeoSearchQueryFactory()
                {
                    
                }
                
                IEegeoSearchQuery* EegeoSearchQueryFactory::CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                                  Eegeo::Helpers::ICallback0& completionCallback)
                {
                    if (m_interiorInteractionModel.HasInteriorModel() && query.IsCategory() && query.ShouldTryInteriorSearch())
                    {
                        
                        const Eegeo::Resources::Interiors::InteriorsModel& interiorsModel = *m_interiorInteractionModel.GetInteriorModel();
                        return Eegeo_NEW(EegeoInteriorSearchQuery)(m_webRequestFactory,
                                                                   m_urlEncoder,
                                                                   query,
                                                                   m_serviceUrl,
                                                                   m_apiKey,
                                                                   interiorsModel.GetId(),
                                                                   m_interiorInteractionModel.GetSelectedFloorIndex(),
                                                                   completionCallback);
                    }
                    else
                    {
                        return Eegeo_NEW(EegeoSearchQuery)(m_webRequestFactory,
                                                           m_urlEncoder,
                                                           query,
                                                           m_serviceUrl,
                                                           m_apiKey,
                                                           completionCallback);
                    }
                }
            }
        }
    }
}
