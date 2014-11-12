// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Rendering.h"
#include "ModalBackgroundView.h"
#include "Modules.h"
#include "IModalBackgroundNativeViewModule.h"
#include "UiToNativeMessageBus.h"
#include "ModalBackgroundNativeModalityObserver.h"

namespace ExampleApp
{
namespace ModalBackground
{
class ModalBackgroundNativeViewModule : public IModalBackgroundNativeViewModule, private Eegeo::NonCopyable
{
private:
	ModalBackgroundView* m_pModalBackgroundView;
	ModalBackgroundNativeModalityObserver* m_pModalBackgroundNativeModalityObserver;

	Eegeo::Rendering::RenderableFilters& m_renderableFilters;

public:
	ModalBackgroundNativeViewModule(
	    Eegeo::Modules::Core::RenderingModule& renderingModule,
	    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageCatalog
	);

	~ModalBackgroundNativeViewModule();
};
}
}
