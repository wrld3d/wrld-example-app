// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuViewModel.h"
#include "OpenableControlViewModelBase.h"
#include "ScreenControlViewModelBase.h"
#include "IIdentity.h"
#include "MenuOpenableControl.h"
#include "MenuScreenControl.h"
#include "MenuSectionsViewModel.h"
#include "Menu.h"
#include "Reaction.h"
#include <vector>

namespace ExampleApp
{
namespace Menu
{
class MenuViewModel : public IMenuViewModel, private Eegeo::NonCopyable
{
	Eegeo::Helpers::TIdentity m_identity;
	MenuOpenableControl m_openViewModel;
	MenuScreenControl m_screenViewModel;
	MenuSectionsViewModel m_sectionsViewModel;

public:
	MenuViewModel(bool isInitiallyOnScreen,
	              Eegeo::Helpers::TIdentity identity,
	              Reaction::IReactionControllerModel& reactionControllerModel);

	Eegeo::Helpers::TIdentity GetIdentity() const;

	void AddToScreen();

	void RemoveFromScreen();

	void UpdateOnScreenState(float onScreenState);

	void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback);

	void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback);

	bool IsFullyOffScreen() const;

	bool IsFullyOnScreen() const;

	float OnScreenState() const;

	bool HasReactorControl() const;

	bool TryAcquireReactorControl();

	void ReleaseReactorControl();

	bool Open();

	bool Close();

	void UpdateOpenState(float openState);

	void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>& callback);

	void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>& callback);

	bool IsFullyOpen() const;

	bool IsFullyClosed() const;

	float OpenState() const;

	void AddSection(IMenuSectionViewModel& section);
	void RemoveSection(IMenuSectionViewModel& section);

	size_t SectionsCount() const
	{
		return m_sectionsViewModel.SectionsCount();
	}

	IMenuSectionViewModel& GetMenuSection(int index) const;

};
}
}
