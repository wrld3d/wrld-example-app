// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "Search.h"
#include "SearchResultPoi.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapItemModel : public WorldPins::IWorldPinSelectionHandler, private Eegeo::NonCopyable
		{
			Search::SearchResultModel& m_searchResultModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

		public:
			SearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel,
			                           ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultOnMapItemModel();

			void SelectPin();
		};
	}
}
