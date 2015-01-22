// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalityController.h"
#include "IModalityModel.h"
#include "MathFunc.h"

namespace ExampleApp
{
	namespace Modality
	{
		ModalityController::ModalityController(IModalityModel& modalityModel,
		                                       const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& viewModels)
			: m_modalityModel(modalityModel)
			, m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ModalityController, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &ModalityController::MenuOpenStateChangeHandler))
			, m_viewModels(viewModels)
		{

			for(std::vector<OpenableControlViewModel::IOpenableControlViewModel*>::iterator it = m_viewModels.begin();
			        it != m_viewModels.end();
			        ++ it)
			{
				OpenableControlViewModel::IOpenableControlViewModel& viewModel = **it;
				viewModel.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
			}
		}

		ModalityController::~ModalityController()
		{
			for(std::vector<OpenableControlViewModel::IOpenableControlViewModel*>::iterator it = m_viewModels.begin();
			        it != m_viewModels.end();
			        ++ it)
			{
				OpenableControlViewModel::IOpenableControlViewModel& viewModel = **it;
				viewModel.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
			}

			m_viewModels.clear();

			Eegeo_DELETE m_pMenuOpenStateChangedCallback;
		}

		float ModalityController::GetModality() const
		{
			float max = 0.f;

			for(std::vector<OpenableControlViewModel::IOpenableControlViewModel*>::const_iterator it = m_viewModels.begin();
			        it != m_viewModels.end();
			        ++ it)
			{
				OpenableControlViewModel::IOpenableControlViewModel& viewModel = **it;

				if(viewModel.OpenState() > max)
				{
					max = viewModel.OpenState();
				}
			}

			return max;
		}

		void ModalityController::MenuOpenStateChangeHandler(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState)
		{
			float modality = GetModality();
			m_modalityModel.SetModality(modality);
		}
	}
}
