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
                                                   const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels,
                                                   Menu::View::IMenuIgnoredReactionModel& ignoredReactionModel)
                : m_modalityModel(modalityModel)
                , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ModalityController, OpenableControl::View::IOpenableControlViewModel&, float>))(this, &ModalityController::MenuOpenStateChangeHandler))
                , m_viewModels(viewModels)
                , m_ignoredReactionModel(ignoredReactionModel)
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

                if (m_ignoredReactionModel.IsIgnored(identity))
                {
                    return;
                }
                
                m_modalityModel.SetModality(openState);
            }
        }
    }
}
