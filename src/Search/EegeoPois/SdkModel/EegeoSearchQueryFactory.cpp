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
                                                                 const Eegeo::Web::ApiTokenModel& apiTokenModel)
                : m_webRequestFactory(webRequestFactory)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_urlEncoder(urlEncoder)
                , m_serviceUrl(serviceUrl)
                , m_apiTokenModel(apiTokenModel)
                {
                    
                }
                
                EegeoSearchQueryFactory::~EegeoSearchQueryFactory()
                {
                    
                }
                
                IEegeoSearchQuery* EegeoSearchQueryFactory::CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                                  Eegeo::Helpers::ICallback0& completionCallback)
                {
                    std::string lowerCaseQueryString = query.Query();
                    std::transform(lowerCaseQueryString.begin(), lowerCaseQueryString.end(), lowerCaseQueryString.begin(), tolower);
                    Search::SdkModel::SearchQuery lowerCaseSearchQuery(lowerCaseQueryString, query.IsTag(), query.ShouldTryInteriorSearch(), query.Location(), query.Radius());
                    
                    const Eegeo::Resources::Interiors::InteriorsModel* interiorsModel = m_interiorInteractionModel.GetInteriorModel();
                    if (m_interiorInteractionModel.HasInteriorModel() && query.IsTag() && query.ShouldTryInteriorSearch())
                    {
                        const Eegeo::Resources::Interiors::InteriorId interiorId(!query.InteriorId().empty() ? query.InteriorId() : interiorsModel->GetId());
                        
                        if(!query.InteriorId().empty())
                        {
                            interiorId.Value() = query.InteriorId();
                        }
                        
                        return Eegeo_NEW(EegeoInteriorSearchQuery)(m_webRequestFactory,
                                                                   m_urlEncoder,
                                                                   lowerCaseSearchQuery,
                                                                   m_serviceUrl,
                                                                   m_apiTokenModel,
                                                                   interiorId,
                                                                   m_interiorInteractionModel.GetSelectedFloorIndex(),
                                                                   completionCallback);
                    }
                    else
                    {
                        Eegeo::Resources::Interiors::InteriorId interiorId(Eegeo::Resources::Interiors::InteriorId::NullId());
                        
                        if (!query.InteriorId().empty())
                        {
                            interiorId = query.InteriorId();
                        }
                        else if (interiorsModel != nullptr)
                        {
                            interiorId = interiorsModel->GetId();
                        }

                        return Eegeo_NEW(EegeoSearchQuery)(m_webRequestFactory,
                                                           m_urlEncoder,
                                                           lowerCaseSearchQuery,
                                                           m_serviceUrl,
                                                           m_apiTokenModel,
                                                           interiorId,
                                                           m_interiorInteractionModel.GetSelectedFloorIndex(),
                                                           completionCallback);
                    }
                }
            }
        }
    }
}
