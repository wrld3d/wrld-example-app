// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CombinedSearchServiceModule.h"
#include "CombinedSearchService.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                CombinedSearchServiceModule::CombinedSearchServiceModule(std::map<std::string, Search::SdkModel::ISearchServiceModule*> searchServiceModules,
                                                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
                : m_pSearchService(NULL)
                {
                    std::map<std::string,Search::SdkModel::ISearchService*> searchServices;

                    for(std::map<std::string, Search::SdkModel::ISearchServiceModule*>::const_iterator it = searchServiceModules.begin(); it != searchServiceModules.end(); ++it)
                    {
                        searchServices[(*it).first] = &(*it).second->GetSearchService();
                    }

                    m_pSearchService = Eegeo_NEW(CombinedSearchService)(searchServices, interiorInteractionModel);
                }
                
                CombinedSearchServiceModule::~CombinedSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                }
                
                Search::SdkModel::ISearchService& CombinedSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
            }
        }
    }
}