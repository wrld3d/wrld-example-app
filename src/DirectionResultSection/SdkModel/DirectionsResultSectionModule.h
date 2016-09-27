// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "IDirectionsResultSectionModule.h"

#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "Search.h"
#include "SearchResultSectionItemSelectedMessageHandler.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultViewClearedObserver.h"
#include "Interiors.h"
#include "AppCamera.h"
#include "Types.h"
#include "DirectionResultSectionWayPointSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            class DirectionsResultSectionModule: public IDirectionsResultSectionModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                ExampleApp::SearchResultSection::View::SearchResultRepositoryObserver* m_pSearchResultRepositoryObserver;
                SearchResultSection::SdkModel::SearchResultSectionItemSelectedMessageHandler* m_pSearchResultSectionItemSelectedMessageHandler;
                SearchResultSection::SdkModel::SearchResultViewClearedObserver* m_pSearchResultViewClearedObserver;
                ExampleApp::SearchResultSection::View::ISearchResultSectionOrder* m_pSearchResultSectionOrder;
                
            public:
                DirectionsResultSectionModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                          Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                          Search::SdkModel::ISearchQueryPerformer& queryPerformer,
                                          CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                          const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                          AppCamera::SdkModel::IAppCameraController& appCameraController,
                                          ExampleAppMessaging::TMessageBus& messageBus);
                
                ~DirectionsResultSectionModule();
                
                Menu::View::IMenuOptionsModel& GetSearchResultSectionOptionsModel() const;
                
                Menu::View::IMenuModel& GetSearchResultSectionModel() const;
                
                ExampleApp::SearchResultSection::View::ISearchResultSectionOrder& GetSearchResultSectionOrder() const;
            };
        }
    }
}