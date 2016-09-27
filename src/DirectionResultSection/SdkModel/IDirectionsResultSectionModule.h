// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "Menu.h"
#include "SearchResultSection.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            class IDirectionsResultSectionModule
            {
            public:
                virtual ~IDirectionsResultSectionModule() { }
                
                virtual Menu::View::IMenuOptionsModel& GetSearchResultSectionOptionsModel() const = 0;
                
                virtual Menu::View::IMenuModel& GetSearchResultSectionModel() const = 0;
                
                virtual ExampleApp::SearchResultSection::View::ISearchResultSectionOrder& GetSearchResultSectionOrder() const = 0;
            };
        }
    }
}