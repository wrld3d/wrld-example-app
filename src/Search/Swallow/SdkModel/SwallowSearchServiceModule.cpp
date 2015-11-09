// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchServiceModule.h"

#include "SwallowOfficeResultMenuOptionSelectedMessageHandler.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchService.h"
#include "SwallowSearchTransitionPinController.h"

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
                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService)
                : m_pSearchService(NULL)
                , m_pSwallowOfficeResultMenuOptionSelectedMessageHandler(NULL)
                , m_pSwallowSearchTransitionPinController(NULL)
                {
                    m_pSearchService = Eegeo_NEW(SwallowSearchService)(SearchConstants::GetCategories(),
                                                                       swallowPoiDbServiceProvider);
                    
                    m_pSwallowOfficeResultMenuOptionSelectedMessageHandler = Eegeo_NEW(SwallowOfficeResultMenuOptionSelectedMessageHandler)(cameraTransitionController, messageBus);
                    
                    m_pSwallowSearchTransitionPinController = Eegeo_NEW(SwallowSearchTransitionPinController)(worldPinsService, cameraTransitionController, appCameraController);
                }
                    
                SwallowSearchServiceModule::~SwallowSearchServiceModule()
                {
                    Eegeo_DELETE m_pSwallowSearchTransitionPinController;
                    
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
                
                SwallowSearchTransitionPinController& SwallowSearchServiceModule::GetSwallowSearchTransitionPinController() const
                {
                    return *m_pSwallowSearchTransitionPinController;
                }
            }
        }
    }
}