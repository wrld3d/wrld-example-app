// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "ISearchResultOnMapModule.h"
#include "SearchResultOnMap.h"
#include "SearchResultPoi.h"
#include "WorldPins.h"
#include "Location.h"
#include "Modality.h"
#include "IIdentity.h"
#include "Rendering.h"
#include "Camera.h"
#include "SearchResultOnMapModalityObserver.h"
#include "SearchResultOnMapItemModelSelectedObserver.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapModule: public ISearchResultOnMapModule, private Eegeo::NonCopyable
		{
		private:
			ISearchResultOnMapModel* m_pSearchResultOnMapModel;
			ISearchResultOnMapFactory* m_pSearchResultOnMapFactory;
			ISearchResultOnMapIconCategoryMapper* m_pSearchResultOnMapIconCategoryMapper;
			SearchResultOnMapModalityObserver* m_pSearchResultOnMapModalityObserver;
			SearchResultOnMapItemModelSelectedObserver* m_pSearchResultOnMapItemModelSelectedObserver;

		public:
			SearchResultOnMapModule(Search::ISearchResultRepository& searchResultRepository,
			                        SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
			                        WorldPins::IWorldPinsService& worldPinsService,
			                        Eegeo::Helpers::IIdentityProvider& identityProvider,
			                        Eegeo::Camera::RenderCamera& renderCamera,
                                    WorldPins::IWorldPinsScaleController& worldPinsScaleController,
			                        ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			                        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultOnMapModule();

			ISearchResultOnMapModel& GetSearchResultOnMapModel() const;

		};
	}
}
