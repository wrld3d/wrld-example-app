// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionModule.h"

#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "Search.h"
#include "SearchResultSectionItemSelectedMessageHandler.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultViewClearedObserver.h"
#include "Interiors.h"
#include "AppCamera.h"
#include "Types.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultSectionModule: public ISearchResultSectionModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                View::SearchResultRepositoryObserver* m_pSearchResultRepositoryObserver;
                SearchResultSectionItemSelectedMessageHandler* m_pSearchResultSectionItemSelectedMessageHandler;
                SearchResultViewClearedObserver* m_pSearchResultViewClearedObserver;
                View::ISearchResultSectionOrder* m_pSearchResultSectionOrder;

            public:
                SearchResultSectionModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                          Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                          Search::SdkModel::ISearchQueryPerformer& queryPerformer,
                                          CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                          const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                          AppCamera::SdkModel::IAppCameraController& appCameraController,
                                          Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                          ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultSectionModule();

                Menu::View::IMenuOptionsModel& GetSearchResultSectionOptionsModel() const;

                Menu::View::IMenuModel& GetSearchResultSectionModel() const;
                
                View::ISearchResultSectionOrder& GetSearchResultSectionOrder() const;
            };
        }
    }
}
