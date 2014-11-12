// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "SearchResultMenu.h"
#include "ISearchResultMenuModule.h"
#include "IIdentity.h"
#include "CameraTransitions.h"
#include "Reaction.h"
#include "SearchResultMenuViewModel.h"
#include "SearchResultMenuItemSelectedMessageHandler.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultAddRemoveHandler.h"
#include "SearchResultMenuSearchQueryPerformedMessageHandler.h"
#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"
#include "SearchResultViewClearedObserver.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultMenuModule: public ISearchResultMenuModule, private Eegeo::NonCopyable
		{
		private:
			Menu::IMenuModel* m_pModel;
			Menu::IMenuOptionsModel* m_pMenuOptionsModel;
			SearchResultMenuViewModel* m_pViewModel;
			SearchResultRepositoryObserver* m_pSearchResultRepositoryObserver;
			Menu::IMenuSectionViewModel* m_pMenuSection;
			SearchResultMenuItemSelectedMessageHandler* m_pSearchResultMenuItemSelectedMessageHandler;
			SearchResultAddRemoveHandler* m_pSearchResultAddRemoveHandler;
			SearchResultMenuSearchQueryPerformedMessageHandler* m_pSearchResultMenuSearchQueryPerformedMessageHandler;
			SearchResultMenuSearchQueryRemovedMessageHandler* m_pSearchResultMenuSearchQueryRemovedMessageHandler;
			SearchResultViewClearedObserver* m_pSearchResultViewClearedObserver;

		public:
			SearchResultMenuModule(
			    Search::ISearchResultRepository& searchResultRepository,
			    Search::ISearchQueryPerformer& queryPerformer,
			    Eegeo::Helpers::IIdentityProvider& identityProvider,
			    CameraTransitions::ICameraTransitionController& cameraTransitionController,
			    Reaction::IReactionControllerModel& reactionControllerModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
			);

			~SearchResultMenuModule();

			Menu::IMenuOptionsModel& GetSearchResultMenuOptionsModel() const;

			Menu::IMenuModel& GetSearchResultMenuModel() const;

			ISearchResultMenuModel& GetSearchResultModel() const;

			Menu::IMenuViewModel& GetMenuViewModel() const;

			ISearchResultMenuViewModel& GetSearchResultMenuViewModel() const;
		};
	}
}
