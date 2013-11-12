//
//  ControlCityThemeExample.cpp
//  ExampleApp
//
//  Created by Tim Jenks on 12/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "ControlCityThemeExample.h"
#include "ICityThemesUpdater.h"
#include "ICityThemesService.h"
#include "ICityThemeRepository.h"
#include "CityThemeData.h"
#include "EegeoWorld.h"

namespace Examples
{
    ControlCityThemeExample::ControlCityThemeExample(Eegeo::Resources::CityThemes::ICityThemesService& themeService,
                                           Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
                                           Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
                                           Eegeo::EegeoWorld& eegeoWorld)
    :themeService(themeService)
    ,themeRepository(themeRepository)
    ,themeUpdater(themeUpdater)
    ,eegeoWorld(eegeoWorld)
    ,themeChanged(false)
    {
    }

    // This method does the following:
    // 1. Disables ICityThemesUpdater - so the App is in sole control of what Theme is active
    // 2. Sets "New York" as the current Theme.
    void ControlCityThemeExample::ChangeTheme()
    {
        const std::string themeToSelect = "New York";
        
        Eegeo_TTY("Starting City Theme Control Example\n");
        
        Eegeo_TTY("Disabling ICityThemesUpdater control over theme selection\n");
        themeUpdater.SetEnabled(false);
        const bool enabled = themeUpdater.GetEnabled();
        Eegeo_TTY("ICityThemesUpdater control over theme selection: %d\n", enabled);
        
        Eegeo_TTY("Obtaining %s ThemeData\n", themeToSelect.c_str());
        const Eegeo::Resources::CityThemes::CityThemeData& themeDataToSelect = themeRepository.GetThemeDataByName(themeToSelect);
        
        Eegeo_TTY("Setting %s Theme\n", themeToSelect.c_str());
        themeService.SetSpecificTheme(themeDataToSelect);
        Eegeo_TTY("%s Theme will now be downloaded and applied asynchronsly. It will remain active until SetSpecificTheme is called again\n", themeToSelect.c_str());
    }
    
    void ControlCityThemeExample::Update()
    {
        if (!themeChanged)
        {
            // This is required so that the theme manifest can be downloaded. Changing theme before EegeoWorld is Initialised will result in ICityThemeRepository being empty.
            if (!eegeoWorld.Initialising())
            {
                ChangeTheme();
                themeChanged = true;
            }
        }
    }
}