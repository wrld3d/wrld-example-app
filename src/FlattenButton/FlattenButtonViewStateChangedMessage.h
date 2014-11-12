// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
	namespace FlattenButton
	{
		class FlattenButtonViewStateChangedMessage
		{
			bool m_isFlattened;

		public:
			FlattenButtonViewStateChangedMessage(bool isFlattened)
				: m_isFlattened(isFlattened)
			{

			}

			bool IsFlattened() const
			{
				return m_isFlattened;
			}
		};
	}
}
