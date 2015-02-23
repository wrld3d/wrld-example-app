// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityModel.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityModel::ModalityModel()
                :m_modality(0.f)
            {

            }

            ModalityModel::~ModalityModel()
            {

            }

            bool ModalityModel::IsModalEnabled() const
            {
                return m_modality != 0.f;
            }

            float ModalityModel::GetModality() const
            {
                return m_modality;
            }

            void ModalityModel::InsertModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback)
            {
                m_modalityChangedCallbacks.AddCallback(modalityChangedCallback);
            }

            void ModalityModel::RemoveModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback)
            {
                m_modalityChangedCallbacks.RemoveCallback(modalityChangedCallback);
            }

            void ModalityModel::SetModality(float modality)
            {
                Eegeo_ASSERT(modality >= 0.f && modality <= 1.f, "Invalid modality value %f, valid range for modality is 0.0 to 1.0 inclusive.\n", modality);
                m_modality = modality;
                m_modalityChangedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
