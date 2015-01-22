// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapController.h"
#include "IWorldPinOnMapView.h"
#include "IWorldPinInFocusViewModel.h"
#include "IModalityModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapController::WorldPinOnMapController(IWorldPinOnMapView& view,
                    IWorldPinInFocusViewModel& viewModel,
                    ScreenControl::View::IScreenControlViewModel& screenControlViewModel,
                    Modality::View::IModalityModel& modalityModel)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_screenControlViewModel(screenControlViewModel)
                , m_modalityModel(modalityModel)
                , m_viewSelectedCallback(this, &WorldPinOnMapController::OnSelected)
                , m_viewModelOpenedCallback(this, &WorldPinOnMapController::OnOpened)
                , m_viewModelClosedCallback(this, &WorldPinOnMapController::OnClosed)
                , m_viewModelUpdateCallback(this, &WorldPinOnMapController::OnUpdated)
                , m_viewModelScreenStateCallback(this, &WorldPinOnMapController::OnScreenStateUpdated)
            {
                m_view.InsertSelectedCallback(m_viewSelectedCallback);
                m_viewModel.InsertOpenedCallback(m_viewModelOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewModelClosedCallback);
                m_viewModel.InsertUpdateCallback(m_viewModelUpdateCallback);
                m_screenControlViewModel.InsertOnScreenStateChangedCallback(m_viewModelScreenStateCallback);

                if (m_viewModel.IsOpen())
                {
                    OnOpened();
                }
                else
                {
                    OnClosed();
                }
            }

            WorldPinOnMapController::~WorldPinOnMapController()
            {
                m_screenControlViewModel.RemoveOnScreenStateChangedCallback(m_viewModelScreenStateCallback);
                m_viewModel.RemoveUpdateCallback(m_viewModelUpdateCallback);
                m_viewModel.RemoveClosedCallback(m_viewModelClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpenedCallback);
                m_view.RemoveSelectedCallback(m_viewSelectedCallback);
            }

            void WorldPinOnMapController::OnSelected()
            {
                if(!m_modalityModel.IsModalEnabled())
                {
                    if(m_viewModel.IsOpen())
                    {
                        m_viewModel.SelectFocussedResult();
                    }
                }
            }

            void WorldPinOnMapController::OnOpened()
            {
                m_view.Open(m_viewModel.GetWorldPinsInFocusModel().GetTitle(), m_viewModel.GetWorldPinsInFocusModel().GetSubtitle());

                OnUpdated();
            }

            void WorldPinOnMapController::OnClosed()
            {
                m_view.Close();
            }

            void WorldPinOnMapController::OnUpdated()
            {
                m_view.UpdateScreenLocation(m_viewModel.ScreenLocation().GetX(), m_viewModel.ScreenLocation().GetY());
            }

            void WorldPinOnMapController::OnScreenStateUpdated(ScreenControl::View::IScreenControlViewModel &screenControlViewModel, float &screenState)
            {
                if(m_viewModel.IsOpen())
                {
                    m_view.UpdateScreenState(screenState);
                }
            }

        }
    }
}
