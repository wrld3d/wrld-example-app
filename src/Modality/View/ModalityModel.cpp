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
                :m_modality(false)
            {

            }

            ModalityModel::~ModalityModel()
            {

            }

            ModalityValue ModalityModel::GetModality() const
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

            void ModalityModel::SetModality(ModalityValue modality)
            {
                m_modality = modality;
                m_modalityChangedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
