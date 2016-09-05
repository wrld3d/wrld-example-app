// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuModel.h"
#include "MenuOptionsModel.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace View
        {
            class WeatherMenuModel : public Menu::View::MenuModel
            {
            };
            
            class WeatherOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                WeatherOptionsModel(const std::shared_ptr<WeatherMenuModel>& menuModel)
                : m_menuModel(menuModel)
                , MenuOptionsModel(*menuModel)
                {
                }
            private:
                std::shared_ptr<WeatherMenuModel> m_menuModel;
            };
        }
        
        namespace SdkModel
        {
            class IWeatherMenuStateModel;
            class IWeatherController;
        }
    }
}
