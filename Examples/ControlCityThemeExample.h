//
//  ControlCityThemeExample.h
//  ExampleApp
//
//  Created by Tim Jenks on 12/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef ExampleApp_ControlCityThemeExample_h
#define ExampleApp_ControlCityThemeExample_h

#include "IExample.h"
#include "CityThemes.h"

namespace Examples
{
    class ControlCityThemeExample : public IExample
    {
    private:
        Eegeo::Resources::CityThemes::ICityThemesService& themeService;
        Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository;
        Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater;
        Eegeo::EegeoWorld& eegeoWorld;
        bool themeChanged;

        void ChangeTheme();
    public:
        ControlCityThemeExample(Eegeo::Resources::CityThemes::ICityThemesService& themeService,
                                Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
                                Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
                                Eegeo::EegeoWorld& eegeoWorld);
        
        void Start() {}
        void Update();
        void Draw() {}
        void Suspend() {}
    };
}


#endif
