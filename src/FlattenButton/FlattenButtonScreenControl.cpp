// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonScreenControl.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		FlattenButtonScreenControl::FlattenButtonScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
			: ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
			, m_identity(identity)
		{
		}

		Eegeo::Helpers::TIdentity FlattenButtonScreenControl::GetIdentity() const
		{
			return m_identity;
		}
	}
}
