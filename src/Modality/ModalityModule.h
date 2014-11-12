// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Modality.h"
#include "IModalityModule.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "UiToNativeMessageBus.h"
#include "ModalityObserver.h"

namespace ExampleApp
{
namespace Modality
{
class ModalityModule: public IModalityModule, private Eegeo::NonCopyable
{
private:
	IModalityController* m_pController;
	IModalityModel* m_pModel;
	ModalityObserver* m_pModalityObserver;

public:
	ModalityModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
	               const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& viewModels);

	~ModalityModule();

	IModalityModel& GetModalityModel() const;
};
}
}
