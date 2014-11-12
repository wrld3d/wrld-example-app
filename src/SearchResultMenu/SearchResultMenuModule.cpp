// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuModule.h"
#include "SearchResultMenu.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "SearchResultMenuViewModel.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultMenuModule::SearchResultMenuModule(Search::ISearchResultRepository& searchResultRepository,
		        Search::ISearchQueryPerformer& searchQueryPerformer,
		        Eegeo::Helpers::IIdentityProvider& identityProvider,
		        CameraTransitions::ICameraTransitionController& cameraTransitionController,
		        Reaction::IReactionControllerModel& reactionControllerModel,
		        ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
		        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		{
			m_pModel = Eegeo_NEW(Menu::MenuModel)();

			m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pModel);

			m_pViewModel = Eegeo_NEW(SearchResultMenuViewModel)(*m_pModel,
			               false,
			               identityProvider.GetNextIdentity(),
			               reactionControllerModel);

			m_pMenuSection = Eegeo_NEW(Menu::MenuSectionViewModel)("Search", "search", *m_pModel, false);
			m_pViewModel->AddSection(*m_pMenuSection);

			m_pSearchResultRepositoryObserver = Eegeo_NEW(SearchResultRepositoryObserver)(
			                                        searchResultRepository,
			                                        nativeToUiMessageBus
			                                    );

			m_pSearchResultMenuItemSelectedMessageHandler = Eegeo_NEW(SearchResultMenuItemSelectedMessageHandler)(
			            cameraTransitionController,
			            uiToNativeMessageBus
			        );

			m_pSearchResultAddRemoveHandler = Eegeo_NEW(SearchResultAddRemoveHandler)(
			                                      *m_pMenuOptionsModel,
			                                      *m_pViewModel,
			                                      nativeToUiMessageBus,
			                                      uiToNativeMessageBus
			                                  );

			m_pSearchResultMenuSearchQueryPerformedMessageHandler = Eegeo_NEW(SearchResultMenuSearchQueryPerformedMessageHandler)(
			            *m_pViewModel,
			            nativeToUiMessageBus
			        );

			m_pSearchResultMenuSearchQueryRemovedMessageHandler = Eegeo_NEW(SearchResultMenuSearchQueryRemovedMessageHandler)(
			            *m_pViewModel,
			            nativeToUiMessageBus
			        );

			m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultViewClearedObserver)(searchQueryPerformer, uiToNativeMessageBus);
		}

		SearchResultMenuModule::~SearchResultMenuModule()
		{
			Eegeo_DELETE m_pSearchResultViewClearedObserver;
			Eegeo_DELETE m_pSearchResultMenuSearchQueryRemovedMessageHandler;
			Eegeo_DELETE m_pSearchResultMenuSearchQueryPerformedMessageHandler;
			Eegeo_DELETE m_pSearchResultAddRemoveHandler;
			Eegeo_DELETE m_pSearchResultMenuItemSelectedMessageHandler;
			Eegeo_DELETE m_pSearchResultRepositoryObserver;
			Eegeo_DELETE m_pMenuSection;
			Eegeo_DELETE m_pViewModel;
			Eegeo_DELETE m_pMenuOptionsModel;
			Eegeo_DELETE m_pModel;
		}

		Menu::IMenuOptionsModel& SearchResultMenuModule::GetSearchResultMenuOptionsModel() const
		{
			return *m_pMenuOptionsModel;
		}

		Menu::IMenuModel& SearchResultMenuModule::GetSearchResultMenuModel() const
		{
			return *m_pModel;
		}

		Menu::IMenuViewModel& SearchResultMenuModule::GetMenuViewModel() const
		{
			return *m_pViewModel;
		}

		ISearchResultMenuViewModel& SearchResultMenuModule::GetSearchResultMenuViewModel() const
		{
			return *m_pViewModel;
		}
	}
}
