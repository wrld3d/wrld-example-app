// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuModule.h"

#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultMenu.h"
#include "SearchResultMenuOrder.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            SearchResultMenuModule::SearchResultMenuModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();

                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pSearchResultRepositoryObserver = Eegeo_NEW(View::SearchResultRepositoryObserver)(searchResultRepository,
                                                                                                    messageBus);

                m_pSearchResultMenuItemSelectedMessageHandler = Eegeo_NEW(SearchResultMenuItemSelectedMessageHandler)(cameraTransitionController,
                                                                                                                      messageBus);

                // TODO: Make sure this message gets published via SearchMenu
                m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultViewClearedObserver)(searchQueryPerformer, messageBus);
                
                m_pSearchResultMenuOrder = Eegeo_NEW(View::SearchResultMenuOrder);
            }

            SearchResultMenuModule::~SearchResultMenuModule()
            {
                Eegeo_DELETE m_pSearchResultMenuOrder;
                Eegeo_DELETE m_pSearchResultViewClearedObserver;
                Eegeo_DELETE m_pSearchResultMenuItemSelectedMessageHandler;
                Eegeo_DELETE m_pSearchResultRepositoryObserver;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }

            Menu::View::IMenuOptionsModel& SearchResultMenuModule::GetSearchResultMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }

            Menu::View::IMenuModel& SearchResultMenuModule::GetSearchResultMenuModel() const
            {
                return *m_pModel;
            }
            
            View::ISearchResultMenuOrder& SearchResultMenuModule::GetSearchResultMenuOrder() const
            {
                return *m_pSearchResultMenuOrder;
            }
        }
    }
}
