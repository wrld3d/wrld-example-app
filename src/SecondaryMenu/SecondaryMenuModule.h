// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "Menu.h"
#include "ISecondaryMenuModule.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "Search.h"
#include "SecondaryMenu.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
namespace SecondaryMenu
{
class SecondaryMenuModule: public ISecondaryMenuModule, private Eegeo::NonCopyable
{
private:
	Menu::IMenuModel* m_pModel;
	Menu::IMenuOptionsModel* m_pMenuOptionsModel;
	Menu::IMenuViewModel* m_pViewModel;
	std::vector<Menu::IMenuSectionViewModel*> m_sections;
	PerformedSearchMessageHandler* m_pPerformedSearchMessageHandler;

public:
	SecondaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
	                    Reaction::IReactionControllerModel& reactionControllerModel,
	                    Search::ISearchQueryPerformer& searchQueryPerformer,
	                    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

	~SecondaryMenuModule();

	void AddMenuSection(const std::string& name, const std::string& icon, Menu::IMenuModel& menuModel, bool isExpandable);

	Menu::IMenuModel& GetSecondaryMenuModel() const;

	Menu::IMenuOptionsModel& GetSecondaryMenuOptionsModel() const;

	Menu::IMenuViewModel& GetSecondaryMenuViewModel() const;
};
}
}
