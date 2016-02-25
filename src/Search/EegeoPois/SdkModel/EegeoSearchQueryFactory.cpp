// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchQuery.h"
#include "EegeoInteriorSearchQuery.h"
#include "InteriorController.h"
#include "InteriorSelectionModel.h"

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
                                                                 const Eegeo::Resources::Interiors::InteriorController& interiorsController,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         const std::string& apiKey)
                : m_webRequestFactory(webRequestFactory)
                , m_interiorsController(interiorsController)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_urlEncoder(urlEncoder)
                , m_apiKey(apiKey)
                {
                    
                }
                
                EegeoSearchQueryFactory::~EegeoSearchQueryFactory()
                {
                    
                }
                
                IEegeoSearchQuery* EegeoSearchQueryFactory::CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                                  Eegeo::Helpers::ICallback0& completionCallback)
                {
                    if (m_interiorsController.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::InteriorInScene && query.IsCategory() && query.IsInterior())
                    {
                        return Eegeo_NEW(EegeoInteriorSearchQuery)(m_webRequestFactory,
                                                                   m_urlEncoder,
                                                                   query,
                                                                   m_apiKey,
                                                                   m_interiorSelectionModel.GetSelectedInteriorId(),
                                                                   m_interiorsController.GetCurrentFloorIndex(),
                                                                   completionCallback);
                    }
                    else
                    {
                        return Eegeo_NEW(EegeoSearchQuery)(m_webRequestFactory,
                                                           m_urlEncoder,
                                                           query,
                                                           m_apiKey,
                                                           completionCallback);
                    }
                }
            }
        }
    }
}