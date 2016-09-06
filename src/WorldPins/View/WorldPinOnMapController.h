// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "WorldPins.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapController : protected Eegeo::NonCopyable
            {
            public:

                WorldPinOnMapController(const std::shared_ptr<IWorldPinOnMapView>& view,
                                        const std::shared_ptr<IWorldPinInFocusViewModel>& viewModel,
                                        const std::shared_ptr<Modality::View::IModalityModel>& modalityModel);
                
                ~WorldPinOnMapController();

            private:

                void OnSelected();

                void OnOpened();
                void OnClosed();
                void OnUpdated();
                void OnScreenStateUpdated(ScreenControl::View::IScreenControlViewModel& screenControlViewModel, float& screenState);

                const std::shared_ptr<IWorldPinOnMapView> m_view;
                const std::shared_ptr<IWorldPinInFocusViewModel> m_viewModel;
                const std::shared_ptr<Modality::View::IModalityModel> m_modalityModel;
                ScreenControl::View::IScreenControlViewModel& m_screenControlViewModel;

                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewSelectedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelClosedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelUpdateCallback;
                Eegeo::Helpers::TCallback2<WorldPinOnMapController, ScreenControl::View::IScreenControlViewModel&, float> m_viewModelScreenStateCallback;
            };
        }
    }
}
