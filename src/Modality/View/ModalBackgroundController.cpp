// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundController.h"
#include "IModalityModel.h"
#include "IModalBackgroundView.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalBackgroundController::ModalBackgroundController(IModalBackgroundView& view, IModalityModel& model)
                : m_view(view)
                , m_model(model)
                , m_modalityChangedCallback(this, &ModalBackgroundController::OnModalityChanged)
            {
                m_model.InsertModalityChangedCallback(m_modalityChangedCallback);
            }

            ModalBackgroundController::~ModalBackgroundController()
            {
                m_model.RemoveModalityChangedCallback(m_modalityChangedCallback);
            }

            void ModalBackgroundController::OnModalityChanged()
            {
                // NOTE: This code is identical to the screen control view model one. Worth creating a viewmodel to define modality as an onScreen value?

                float modalValue = m_model.GetModality();
                if(modalValue == 1.f)
                {
                    m_view.SetFullyActive();
                }
                else if(modalValue == 0.f)
                {
                    m_view.SetFullyInactive();
                }
                else
                {
                    m_view.SetActiveStateToIntermediateValue(modalValue);
                }
            }
        }
    }
}
