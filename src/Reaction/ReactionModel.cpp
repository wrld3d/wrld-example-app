// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ReactionModel.h"
#include "MathFunc.h"
#include "IIdentity.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
namespace Reaction
{
ReactionModel::ReactionModel(IReactionControllerModel& reactionControllerModel,
                             const std::vector<OpenableControlViewModel::IOpenableControlViewModel*>& openables,
                             const std::vector<ScreenControlViewModel::IScreenControlViewModel*>& reactors)
	: m_reactionControllerModel(reactionControllerModel)
	, m_openables(openables)
	, m_reactors(reactors)
	, m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ReactionModel, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &ReactionModel::MenuOpenStateChangeHandler))
{
	for(std::vector<OpenableControlViewModel::IOpenableControlViewModel*>::iterator it = m_openables.begin();
	        it != m_openables.end();
	        ++ it)
	{
		OpenableControlViewModel::IOpenableControlViewModel& openable = **it;
		openable.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
	}
}

ReactionModel::~ReactionModel()
{
	for(std::vector<OpenableControlViewModel::IOpenableControlViewModel*>::iterator it = m_openables.begin();
	        it != m_openables.end();
	        ++ it)
	{
		OpenableControlViewModel::IOpenableControlViewModel& openable = **it;
		openable.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
	}

	Eegeo_DELETE m_pMenuOpenStateChangedCallback;
}

void ReactionModel::UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControlViewModel::IOpenableControlViewModel& changingViewModel, float openState)
{
	for(std::vector<ScreenControlViewModel::IScreenControlViewModel*>::const_iterator it = m_reactors.begin();
	        it != m_reactors.end();
	        ++ it)
	{
		ScreenControlViewModel::IScreenControlViewModel& reactor = **it;

		if(reactor != changingViewModel)
		{
			reactor.UpdateOnScreenState(1.f - openState);
		}
	}
}

void ReactionModel::MenuOpenStateChangeHandler(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState)
{
	if(m_reactionControllerModel.HasModalControl(viewModel.GetIdentity()))
	{
		UpdateOnScreenStatesInReactionToMenuOpenStateChange(viewModel, openState);
	}
}
}
}
