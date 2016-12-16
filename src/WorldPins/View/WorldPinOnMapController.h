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

                WorldPinOnMapController(IWorldPinOnMapView& view,
                                        IWorldPinInFocusViewModel& viewModel,
                                        ScreenControl::View::IScreenControlViewModel& screenControlViewModel,
                                        Modality::View::IModalityModel& modalityModel);
                
                ~WorldPinOnMapController();
                

            private:

                void OnSelected();

                void OnOpened();
                void OnClosed();
                void OnUpdated();
                void OnScreenStateUpdated(ScreenControl::View::IScreenControlViewModel& screenControlViewModel, float& screenState);

                IWorldPinOnMapView& m_view;
                IWorldPinInFocusViewModel& m_viewModel;
                ScreenControl::View::IScreenControlViewModel& m_screenControlViewModel;
                Modality::View::IModalityModel& m_modalityModel;
                
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewSelectedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelClosedCallback;
                Eegeo::Helpers::TCallback0<WorldPinOnMapController> m_viewModelUpdateCallback;
                Eegeo::Helpers::TCallback2<WorldPinOnMapController, ScreenControl::View::IScreenControlViewModel&, float> m_viewModelScreenStateCallback;
            };
        }
    }
}
