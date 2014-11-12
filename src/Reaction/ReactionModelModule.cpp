// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ReactionModelModule.h"
#include "ReactionModel.h"
#include "ReactionControllerModel.h"

namespace ExampleApp
{
namespace Reaction
{
ReactionModelModule::ReactionModelModule(IReactionControllerModel& reactionControllerModel,
        const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& openables,
        const std::vector<ScreenControlViewModel::IScreenControlViewModel*>& reactors)
{
	m_pModel = Eegeo_NEW(ReactionModel)(reactionControllerModel, openables, reactors);
}

ReactionModelModule::~ReactionModelModule()
{
	Eegeo_DELETE m_pModel;
}
}
}
