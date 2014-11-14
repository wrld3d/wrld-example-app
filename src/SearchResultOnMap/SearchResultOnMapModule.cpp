// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapModule.h"
#include "Search.h"
#include "SearchResultOnMap.h"
#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapModel.h"
#include "SearchResultOnMapInFocusViewModel.h"
#include "SearchResultOnMapInFocusController.h"
#include "SearchResultOnMapIconCategoryMapper.h"
#include "IIdentity.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapModule::SearchResultOnMapModule(Search::ISearchResultRepository& searchResultRepository,
                                                         SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                                         WorldPins::IWorldPinsService& worldPinsService,
                                                         Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                         Eegeo::Camera::RenderCamera& renderCamera,
                                                         WorldPins::IWorldPinsScaleController& worldPinsScaleController,
                                                         ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		{
			m_pSearchResultOnMapIconCategoryMapper = Eegeo_NEW(SearchResultOnMapIconCategoryMapper);

			m_pSearchResultOnMapFactory = Eegeo_NEW(SearchResultOnMapFactory)(nativeToUiMessageBus);

			SearchResultOnMapModel* pSearchResultOnMapModel = Eegeo_NEW(SearchResultOnMapModel)(worldPinsService,
			        *m_pSearchResultOnMapFactory,
			        *m_pSearchResultOnMapIconCategoryMapper,
			        searchResultRepository);

			m_pSearchResultOnMapModel = pSearchResultOnMapModel;

			m_pSearchResultOnMapInFocusViewModel = Eegeo_NEW(SearchResultOnMapInFocusViewModel)(searchResultPoiViewModel,
			                                       identityProvider.GetNextIdentity());

			m_pSearchResultOnMapInFocusController = Eegeo_NEW(SearchResultOnMapInFocusController)(*pSearchResultOnMapModel,
			                                        nativeToUiMessageBus,
			                                        worldPinsService,
			                                        renderCamera);

			m_pSearchResultOnMapModalityObserver = Eegeo_NEW(SearchResultOnMapModalityObserver)(worldPinsScaleController,
                                                                                                uiToNativeMessageBus);

			m_pSearchResultOnMapInFocusObserver = Eegeo_NEW(SearchResultOnMapInFocusObserver)(
			        *m_pSearchResultOnMapInFocusViewModel,
			        nativeToUiMessageBus);

			m_pSearchResultOnMapItemModelSelectedObserver = Eegeo_NEW(SearchResultOnMapItemModelSelectedObserver)(searchResultPoiViewModel,
			        nativeToUiMessageBus);
		}

		SearchResultOnMapModule::~SearchResultOnMapModule()
		{
			Eegeo_DELETE m_pSearchResultOnMapItemModelSelectedObserver;
			Eegeo_DELETE m_pSearchResultOnMapInFocusObserver;
			Eegeo_DELETE m_pSearchResultOnMapModalityObserver;
			Eegeo_DELETE m_pSearchResultOnMapInFocusController;
			Eegeo_DELETE m_pSearchResultOnMapInFocusViewModel;
			Eegeo_DELETE m_pSearchResultOnMapModel;
			Eegeo_DELETE m_pSearchResultOnMapFactory;
			Eegeo_DELETE m_pSearchResultOnMapIconCategoryMapper;
		}

		ISearchResultOnMapModel& SearchResultOnMapModule::GetSearchResultOnMapModel() const
		{
			return *m_pSearchResultOnMapModel;
		}

		ISearchResultOnMapInFocusViewModel& SearchResultOnMapModule::GetSearchResultOnMapInFocusViewModel() const
		{
			return *m_pSearchResultOnMapInFocusViewModel;
		}

		ISearchResultOnMapInFocusController& SearchResultOnMapModule::GetSearchResultOnMapInFocusController() const
		{
			return *m_pSearchResultOnMapInFocusController;
		}

		ScreenControlViewModel::IScreenControlViewModel& SearchResultOnMapModule::GetScreenControlViewModel() const
		{
			return m_pSearchResultOnMapInFocusViewModel->GetScreenControlViewModel();
		}
	}
}
