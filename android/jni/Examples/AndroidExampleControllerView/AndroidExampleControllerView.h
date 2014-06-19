// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDEXAMPLECONTROLLERVIEW_H_
#define ANDROIDEXAMPLECONTROLLERVIEW_H_

#include "Types.h"
#include "IExampleControllerView.h"
#include "AndroidNativeState.h"
#include <vector>
#include <string>

namespace Examples
{
class AndroidExampleControllerView : public IExampleControllerView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_exampleUpdatedHandlers;
	std::vector<IUIActionHandler*> m_nextHandlers;
	std::vector<IUIActionHandler*> m_previousHandlers;
	AndroidNativeState& m_nativeState;
	jclass m_androidExampleControllerViewClass;
	jobject m_androidExampleControllerView;
	std::string m_selectedExampleName;

public:
	AndroidExampleControllerView(AndroidNativeState& androidNativeState);

	~AndroidExampleControllerView();

	void Show();

	void AddSelectPreviousExampleHandler(IUIActionHandler& handler);

	void RemoveSelectPreviousExampleHandler(IUIActionHandler& handler);

	void AddSelectNextExampleHandler(IUIActionHandler& handler);

	void SetCurrentExampleName(const std::string& name);

	void RemoveSelectNextExampleHandler(IUIActionHandler& handler);

	void AddExampleSelectedHandler(IUIActionHandler& handler);

	void RemoveExampleSelectedHandler(IUIActionHandler& handler);

	std::string GetSelectedExample();

	void UpdateSelectedExample();

	void SelectPrevious();

	void SelectNext();

	void PopulateExampleList(const std::vector<std::string>& exampleNames);
};
}


#endif /* ANDROIDEXAMPLECONTROLLERVIEW_H_ */
