// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsModule.h"
#include "InitialExperienceDialogsViewModel.h"
#include "InitialExperienceDialogType.h"
#include <map>
#include <string>

namespace
{
    const std::string SearchMenuTitle = "Search Menu";
    const std::string SearchMenuDescription = "Search for places of interest, or customize the look of the world.";

    const std::string PrimaryMenuTitle = "My Menu";
	const std::string PrimaryMenuDescription = "View your pinned locations, see options or information about the app.";

	const std::string CompassTitle = "Compass";
	const std::string CompassDescription = "Shows your orientation. Tap to lock to your GPS position, then slide the camera to unlock.";

	const std::string PinCreationTitle = "Pin creation Menu";
	const std::string PinCreationDescription = "Create your own locations in the world & optionally share them with others.";

	const std::string FlattenTitle = "Flatten button";
	const std::string FlattenDescription = "Flatten the 3D world to see roads clearer.";

	const std::string SourceCodeTitle = "Source code";
	const std::string SourceCodeDescription = "This entire app is open source. You can learn more at http://sdk.eegeo.com";

}

namespace ExampleApp
{
    namespace InitialExperience
    {
		namespace Dialogs
		{
			namespace View
			{
				InitialExperienceDialogsModule::InitialExperienceDialogsModule()
				{
					std::map<InitialExperienceDialogType::Values, std::string> titleMap;
					std::map<InitialExperienceDialogType::Values, std::string> descriptionMap;

					titleMap[InitialExperienceDialogType::SearchMenu] 	= SearchMenuTitle;
					titleMap[InitialExperienceDialogType::PrimaryMenu] 	= PrimaryMenuTitle;
					titleMap[InitialExperienceDialogType::Compass] 		= CompassTitle;
					titleMap[InitialExperienceDialogType::PinCreation] 	= PinCreationTitle;
					titleMap[InitialExperienceDialogType::Flatten] 		= FlattenTitle;
					titleMap[InitialExperienceDialogType::SourceCode] 	= SourceCodeTitle;

					descriptionMap[InitialExperienceDialogType::SearchMenu] 	= SearchMenuDescription;
					descriptionMap[InitialExperienceDialogType::PrimaryMenu] 	= PrimaryMenuDescription;
					descriptionMap[InitialExperienceDialogType::Compass] 		= CompassDescription;
					descriptionMap[InitialExperienceDialogType::PinCreation] 	= PinCreationDescription;
					descriptionMap[InitialExperienceDialogType::Flatten] 		= FlattenDescription;
					descriptionMap[InitialExperienceDialogType::SourceCode] 	= SourceCodeDescription;

					m_pDialogsViewModel = Eegeo_NEW(InitialExperienceDialogsViewModel)(titleMap, descriptionMap);
				}

				InitialExperienceDialogsModule::~InitialExperienceDialogsModule()
				{
					Eegeo_DELETE m_pDialogsViewModel;
				}

				IInitialExperienceDialogsViewModel& InitialExperienceDialogsModule::GetDialogsViewModel() const
				{
					return *m_pDialogsViewModel;
				}
			}
		}
    }
}
