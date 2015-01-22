// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinInFocusScreenControl.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		WorldPinInFocusScreenControl::WorldPinInFocusScreenControl(Eegeo::Helpers::TIdentity identity)
			: ScreenControlViewModel::ScreenControlViewModelBase(false)
			, m_identity(identity)
		{
		}

		Eegeo::Helpers::TIdentity WorldPinInFocusScreenControl::GetIdentity() const
		{
			return m_identity;
		}
	}
}
