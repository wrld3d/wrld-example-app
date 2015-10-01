// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchServiceModule.h"

#include "SwallowOfficeResultMenuOptionSelectedMessageHandler.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchServiceModule::SwallowSearchServiceModule(SwallowPoiDb::SwallowPoiDbServiceProvider& swallowPoiDbServiceProvider,
                                                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                       ExampleAppMessaging::TMessageBus& messageBus)
                : m_pSearchService(NULL)
                , m_pSwallowOfficeResultMenuOptionSelectedMessageHandler(NULL)
                {
                    m_pSearchService = Eegeo_NEW(SwallowSearchService)(SearchConstants::GetCategories(),
                                                                       swallowPoiDbServiceProvider);
                    
                    m_pSwallowOfficeResultMenuOptionSelectedMessageHandler = Eegeo_NEW(SwallowOfficeResultMenuOptionSelectedMessageHandler)(cameraTransitionController, messageBus);
                }
                    
                SwallowSearchServiceModule::~SwallowSearchServiceModule()
                {
                    Eegeo_DELETE m_pSwallowOfficeResultMenuOptionSelectedMessageHandler;
                    
                    Eegeo_DELETE m_pSearchService;
                }
                    
                Search::SdkModel::ISearchService& SwallowSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
                    
                std::vector<CategorySearch::View::CategorySearchModel> SwallowSearchServiceModule::GetCategorySearchModels() const
                {
                    return SearchConstants::GetCategorySearchModels();
                }
            }
        }
    }
}