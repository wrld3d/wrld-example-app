// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionModule.h"

#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultSection.h"
#include "SearchResultSectionOrder.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            SearchResultSectionModule::SearchResultSectionModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                 Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                 const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                                                 AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                 Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();

                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pSearchResultRepositoryObserver = Eegeo_NEW(View::SearchResultRepositoryObserver)(searchResultRepository,
                                                                                                    messageBus);

                m_pSearchResultSectionItemSelectedMessageHandler = Eegeo_NEW(SearchResultSectionItemSelectedMessageHandler)(cameraTransitionController,
                                                                                                                            searchRefreshService,
                                                                                                                            messageBus);
                
                m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultViewClearedObserver)(searchQueryPerformer, messageBus);
                
                m_pSearchResultSectionOrder = Eegeo_NEW(View::SearchResultSectionOrder)();
            }

            SearchResultSectionModule::~SearchResultSectionModule()
            {
                Eegeo_DELETE m_pSearchResultSectionOrder;
                Eegeo_DELETE m_pSearchResultViewClearedObserver;
                Eegeo_DELETE m_pSearchResultSectionItemSelectedMessageHandler;
                Eegeo_DELETE m_pSearchResultRepositoryObserver;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }

            Menu::View::IMenuOptionsModel& SearchResultSectionModule::GetSearchResultSectionOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }

            Menu::View::IMenuModel& SearchResultSectionModule::GetSearchResultSectionModel() const
            {
                return *m_pModel;
            }
            
            View::ISearchResultSectionOrder& SearchResultSectionModule::GetSearchResultSectionOrder() const
            {
                return *m_pSearchResultSectionOrder;
            }
        }
    }
}
