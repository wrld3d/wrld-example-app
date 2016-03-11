// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityController.h"
#include "IModalityModel.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityController::ModalityController(IModalityModel& modalityModel,
                                                   const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels)
                : m_modalityModel(modalityModel)
                , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ModalityController, OpenableControl::View::IOpenableControlViewModel&, float>))(this, &ModalityController::MenuOpenStateChangeHandler))
                , m_viewModels(viewModels)
            {

                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_viewModels.begin();
                        it != m_viewModels.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& viewModel = **it;
                    viewModel.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }
            }

            ModalityController::~ModalityController()
            {
                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_viewModels.begin();
                        it != m_viewModels.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& viewModel = **it;
                    viewModel.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }

                m_viewModels.clear();

                Eegeo_DELETE m_pMenuOpenStateChangedCallback;
            }

            void ModalityController::AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                m_ignoredMenuIdentities.push_back(identity);

                Eegeo_TTY("IdentityIgnored: %d", identity);
            }

            void ModalityController::RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                std::vector<Eegeo::Helpers::TIdentity>::iterator result = std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity);
                
                m_ignoredMenuIdentities.erase(result);
            }

            float ModalityController::GetModality() const
            {
                float max = 0.f;

                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::const_iterator it = m_viewModels.begin();
                        it != m_viewModels.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& viewModel = **it;

                    if(viewModel.OpenState() > max)
                    {
                        max = viewModel.OpenState();
                    }
                }

                return max;
            }

            void ModalityController::MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                Eegeo::Helpers::TIdentity identity = viewModel.GetIdentity();

                if (std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity) != m_ignoredMenuIdentities.end())
                {
                    return;
                }
                
                float modality = GetModality();
                m_modalityModel.SetModality(modality);
            }
        }
    }
}
