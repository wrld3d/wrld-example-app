// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Reaction.h"

namespace ExampleApp
{
	namespace Reaction
	{
		class IReactionControllerModule
		{
		public:
			virtual ~IReactionControllerModule() { }

			virtual IReactionControllerModel& GetReactionControllerModel() const = 0;
		};
	}
}
