// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityController.h"
#include "IModalityModel.h"
#include "MathFunc.h"
#include "ModalityIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityController::ModalityController(const std::shared_ptr<IModalityModel>& modalityModel,
                                                   const std::shared_ptr<OpenableControl::View::TOpenables>& openables,
                                                   const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel>& ignoredReactionModel)
                : m_modalityModel(modalityModel)
                , m_menuOpenStateChangedCallback(this, &ModalityController::MenuOpenStateChangeHandler)
                , m_openableAdded(this, &ModalityController::OnOpenableAdded)
                , m_openableRemoved(this, &ModalityController::OnOpenableRemoved)
                , m_openables(openables)
                , m_ignoredReactionModel(ignoredReactionModel)
            {
                m_openables->InsertItemAddedCallback(m_openableAdded);
                m_openables->InsertItemRemovedCallback(m_openableRemoved);
            }

            ModalityController::~ModalityController()
            {
                m_openables->RemoveItemRemovedCallback(m_openableRemoved);
                m_openables->RemoveItemAddedCallback(m_openableAdded);
            }

            float ModalityController::GetModality() const
            {
                float max = 0.f;

                for(size_t i = 0; i < m_openables->GetItemCount(); ++i)
                {
                    OpenableControl::View::IOpenableControlViewModel& viewModel = *m_openables->GetItemAtIndex(i);

                    if(viewModel.OpenState() > max)
                    {
                        max = viewModel.OpenState();
                    }
                }

                return max;
            }
            
            void ModalityController::OnOpenableAdded(OpenableControl::View::IOpenableControlViewModel*& openable)
            {
                openable->InsertOpenStateChangedCallback(m_menuOpenStateChangedCallback);
            }
            
            void ModalityController::OnOpenableRemoved(OpenableControl::View::IOpenableControlViewModel*& openable)
            {
                openable->RemoveOpenStateChangedCallback(m_menuOpenStateChangedCallback);
            }

            void ModalityController::MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                Eegeo::Helpers::TIdentity identity = viewModel.GetIdentity();

                if (m_ignoredReactionModel->IsIgnored(identity))
                {
                    return;
                }
                
                m_modalityModel->SetModality(openState);
            }
        }
    }
}
