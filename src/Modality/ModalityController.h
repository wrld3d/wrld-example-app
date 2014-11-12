// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Modality.h"
#include "IModalityController.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
	namespace Modality
	{
		class ModalityController : public IModalityController, private Eegeo::NonCopyable
		{
			IModalityModel& m_modalityModel;
			std::vector<OpenableControlViewModel::IOpenableControlViewModel*> m_viewModels;
			Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

		public:
			ModalityController(IModalityModel& modalityModel,
			                   const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& viewModels);

			~ModalityController();

		private:

			float GetModality() const;

			void MenuOpenStateChangeHandler(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);
		};
	}
}
