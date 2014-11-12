// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "IAboutPageModule.h"
#include "AboutPageViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"

namespace ExampleApp
{
namespace AboutPage
{
class AboutPageModule : public IAboutPageModule, private Eegeo::NonCopyable
{
	IAboutPageModel* m_pAboutPageModel;
	AboutPageViewModel* m_pAboutPageViewModel;

public:
	AboutPageModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
	                Reaction::IReactionControllerModel& reactionControllerModel);

	~AboutPageModule();

	IAboutPageModel& GetAboutPageModel() const;

	IAboutPageViewModel& GetAboutPageViewModel() const;

	OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
};
}
}
