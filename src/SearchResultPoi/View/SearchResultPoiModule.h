// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultPoi.h"
#include "ISearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"

namespace ExampleApp
{
	namespace SearchResultPoi
	{
		class SearchResultPoiModule: public ISearchResultPoiModule, private Eegeo::NonCopyable
		{
		private:
			SearchResultPoiViewModel* m_pSearchResultPoiViewModel;

		public:
			SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
			                      Reaction::IReactionControllerModel& reactionControllerModel);

			~SearchResultPoiModule();

			ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const;

			OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
		};
	}
}
