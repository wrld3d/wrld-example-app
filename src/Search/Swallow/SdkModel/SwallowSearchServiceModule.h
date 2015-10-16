// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"

#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "SwallowPoiDb.h"
#include "SwallowSearch.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    Search::SdkModel::ISearchService* m_pSearchService;
                    SwallowSearchTransitionPinController* m_pSwallowSearchTransitionPinController;
                    SwallowOfficeResultMenuOptionSelectedMessageHandler* m_pSwallowOfficeResultMenuOptionSelectedMessageHandler;
                    
                public:
                    SwallowSearchServiceModule(SwallowPoiDb::SwallowPoiDbServiceProvider& swallowPoiDbServiceProvider,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               WorldPins::SdkModel::IWorldPinsService& worldPinsService);
                    
                    ~SwallowSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                    
                    SwallowSearchTransitionPinController& GetSwallowSearchTransitionPinController() const;
                };
            }
        }
    }
}