// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "IPlaceJumpController.h"
#include "IPlaceJumpsModel.h"
#include "Logger.h"
#include "IMenuViewModel.h"
#include "UiToNativeMessageBus.h"
#include "PlaceJumpSelectedMessage.h"

namespace ExampleApp
{
namespace PlaceJumps
{
class PlaceJumpMenuOption : public Menu::IMenuOption
{
public:
	PlaceJumpMenuOption(PlaceJumpModel jumpModel,
	                    ExampleApp::Menu::IMenuViewModel& menuViewModel,
	                    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		: m_jumpModel(jumpModel)
		, m_menuViewModel(menuViewModel)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
	{
	}

	void Select()
	{
		m_menuViewModel.Close();
		m_uiToNativeMessageBus.Publish(PlaceJumpSelectedMessage(m_jumpModel));
	}

private:

	PlaceJumpModel m_jumpModel;
	ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
	ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
};

}
}
