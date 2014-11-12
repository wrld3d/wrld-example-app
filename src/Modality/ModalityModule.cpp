// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include "ModalityModule.h"
#include "ModalityModel.h"
#include "ModalityController.h"

namespace ExampleApp
{
namespace Modality
{
ModalityModule::ModalityModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                               const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& viewModels)
{
	m_pModel = Eegeo_NEW(ModalityModel)();

	m_pController = Eegeo_NEW(ModalityController)(*m_pModel,
	                viewModels);

	m_pModalityObserver = Eegeo_NEW(ModalityObserver)(*m_pModel, uiToNativeMessageBus);
}

ModalityModule::~ModalityModule()
{
	Eegeo_DELETE m_pModalityObserver;
	Eegeo_DELETE m_pModel;
}

IModalityModel& ModalityModule::GetModalityModel() const
{
	return *m_pModel;
}
}
}
