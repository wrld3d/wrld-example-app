// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuModule.h"

#include "SearchResultMenu.h"
#include "SearchResultMenuOrder.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "SearchResultMenuViewModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            SearchResultMenuModule::SearchResultMenuModule(Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();

                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);

                m_pViewModel = Eegeo_NEW(View::SearchResultMenuViewModel)(*m_pModel,
                               false,
                               identityProvider.GetNextIdentity(),
                               reactionControllerModel);

                m_pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)("Search", "search", *m_pModel, false);
                m_pViewModel->AddSection(*m_pMenuSection);

                m_pSearchResultRepositoryObserver = Eegeo_NEW(View::SearchResultRepositoryObserver)(
                                                        searchResultRepository,
                                                        messageBus
                                                    );

                m_pSearchResultMenuItemSelectedMessageHandler = Eegeo_NEW(SearchResultMenuItemSelectedMessageHandler)(
                            cameraTransitionController,
                            messageBus
                        );

                m_pSearchResultMenuSearchQueryPerformedMessageHandler = Eegeo_NEW(View::SearchResultMenuSearchQueryPerformedMessageHandler)(
                            *m_pViewModel,
                            messageBus
                        );

                m_pSearchResultMenuSearchQueryRemovedMessageHandler = Eegeo_NEW(View::SearchResultMenuSearchQueryRemovedMessageHandler)(
                            *m_pViewModel,
                            messageBus
                        );
                
                m_pSearchResultMenuAppModeMessageHandler = Eegeo_NEW(View::SearchResultMenuAppModeMessageHandler)(*m_pViewModel, messageBus);

                m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultViewClearedObserver)(searchQueryPerformer, messageBus);
                
                m_pSearchResultMenuOrder = Eegeo_NEW(View::SearchResultMenuOrder);
            }

            SearchResultMenuModule::~SearchResultMenuModule()
            {
                Eegeo_DELETE m_pSearchResultMenuOrder;
                Eegeo_DELETE m_pSearchResultViewClearedObserver;
                Eegeo_DELETE m_pSearchResultMenuAppModeMessageHandler;
                Eegeo_DELETE m_pSearchResultMenuSearchQueryRemovedMessageHandler;
                Eegeo_DELETE m_pSearchResultMenuSearchQueryPerformedMessageHandler;
                Eegeo_DELETE m_pSearchResultMenuItemSelectedMessageHandler;
                Eegeo_DELETE m_pSearchResultRepositoryObserver;
                Eegeo_DELETE m_pMenuSection;
                Eegeo_DELETE m_pViewModel;
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

            Menu::View::IMenuViewModel& SearchResultMenuModule::GetMenuViewModel() const
            {
                return *m_pViewModel;
            }

            View::ISearchResultMenuViewModel& SearchResultMenuModule::GetSearchResultMenuViewModel() const
            {
                return *m_pViewModel;
            }
            
            View::ISearchResultMenuOrder& SearchResultMenuModule::GetSearchResultMenuOrder() const
            {
                return *m_pSearchResultMenuOrder;
            }
        }
    }
}
