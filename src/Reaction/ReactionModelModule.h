// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Reaction.h"
#include "ReactionModel.h"
#include "OpenableControlViewModelIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "IReactionModelModule.h"

namespace ExampleApp
{
	namespace Reaction
	{
		class ReactionModelModule: public IReactionModelModule, private Eegeo::NonCopyable
		{
		private:
			IReactionModel* m_pModel;
		public:
			ReactionModelModule(IReactionControllerModel& reactionControllerModel,
			                    const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& openables,
			                    const std::vector<ScreenControlViewModel::IScreenControlViewModel*>& reactors);

			~ReactionModelModule();
		};
	}
}
