// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "OpenableControlViewModelBase.h"
#include "Reaction.h"

namespace ExampleApp
{
namespace Menu
{
class MenuOpenableControl : public OpenableControlViewModel::OpenableControlViewModelBase, private Eegeo::NonCopyable
{
	Eegeo::Helpers::TIdentity m_identity;

public:
	MenuOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel);

	Eegeo::Helpers::TIdentity GetIdentity() const;
};
}
}
