// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinOnMapViewController.h"
#include "Types.h"
#include "WorldPinOnMapView.h"
#include "IWorldPinInFocusViewModel.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

@class WorldPinOnMapViewController;

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewControllerInterop : private Eegeo::NonCopyable
		{
			WorldPinOnMapViewController* m_pInstance;
            WorldPins::IWorldPinInFocusViewModel& m_worldPinInFocusViewModel;
			ScreenControlViewModel::IScreenControlViewModel& m_worldPinOnMapInFocusScreenControlViewModel;

			Eegeo::Helpers::TCallback0<WorldPinOnMapViewControllerInterop> m_worldPinOnMapFocusOpenedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewControllerInterop> m_worldPinOnMapFocusClosedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewControllerInterop> m_worldPinOnMapFocusUpdatedCallback;
			Eegeo::Helpers::TCallback2<WorldPinOnMapViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float> m_onScreenStateChangedCallback;

            void WorldPinOnMapFocusOpenedCallback()
			{
				[m_pInstance open];
			}

			void WorldPinOnMapFocusClosedCallback()
			{
				[m_pInstance close];
			}

            void WorldPinOnMapFocusUpdatedCallback()
			{
				[m_pInstance updateScreenLocation];
			}

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
			{
				[m_pInstance handleScreenStateChanged: m_worldPinOnMapInFocusScreenControlViewModel.OnScreenState()];
			}

		public:
			WorldPinOnMapViewControllerInterop(WorldPinOnMapViewController* pInstance,
                                               IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                               ScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel)
				: m_pInstance(pInstance)
				, m_worldPinInFocusViewModel(worldPinInFocusViewModel)
				, m_worldPinOnMapInFocusScreenControlViewModel(worldPinOnMapInFocusScreenControlViewModel)
				, m_worldPinOnMapFocusOpenedCallback(this, &WorldPinOnMapViewControllerInterop::WorldPinOnMapFocusOpenedCallback)
				, m_worldPinOnMapFocusClosedCallback(this, &WorldPinOnMapViewControllerInterop::WorldPinOnMapFocusClosedCallback)
				, m_worldPinOnMapFocusUpdatedCallback(this, &WorldPinOnMapViewControllerInterop::WorldPinOnMapFocusUpdatedCallback)
				, m_onScreenStateChangedCallback(this, &WorldPinOnMapViewControllerInterop::OnScreenStateChangedCallback)
			{
				m_worldPinInFocusViewModel.InsertOpenedCallback(m_worldPinOnMapFocusOpenedCallback);
				m_worldPinInFocusViewModel.InsertClosedCallback(m_worldPinOnMapFocusClosedCallback);
				m_worldPinInFocusViewModel.InsertUpdateCallback(m_worldPinOnMapFocusUpdatedCallback);

				m_worldPinOnMapInFocusScreenControlViewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
			}

			~WorldPinOnMapViewControllerInterop()
			{
				m_worldPinOnMapInFocusScreenControlViewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChangedCallback);

				m_worldPinInFocusViewModel.RemoveUpdateCallback(m_worldPinOnMapFocusUpdatedCallback);
				m_worldPinInFocusViewModel.RemoveOpenedCallback(m_worldPinOnMapFocusOpenedCallback);
				m_worldPinInFocusViewModel.RemoveClosedCallback(m_worldPinOnMapFocusClosedCallback);
			}
		};
	}
}
