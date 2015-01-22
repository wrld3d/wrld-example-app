// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsOpenableControl.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		MyPinDetailsOpenableControl::MyPinDetailsOpenableControl(Eegeo::Helpers::TIdentity identity,
		        Reaction::IReactionControllerModel& reactionControllerModel)
			: OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
			, m_identity(identity)
		{
		}

		Eegeo::Helpers::TIdentity MyPinDetailsOpenableControl::GetIdentity() const
		{
			return m_identity;
		}
	}
}
