// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Reaction.h"
#include "IReactionControllerModule.h"

namespace ExampleApp
{
	namespace Reaction
	{
		class ReactionControllerModule: public IReactionControllerModule, private Eegeo::NonCopyable
		{
		private:
			IReactionControllerModel* m_pReactionControllerModel;

		public:
			ReactionControllerModule();

			~ReactionControllerModule();

			IReactionControllerModel& GetReactionControllerModel() const;
		};
	}
}
