// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultMenu.h"
#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class ISearchResultMenuViewModel
            {
            public:
                virtual ~ISearchResultMenuViewModel() { }

                virtual bool CanInteract() const = 0;

                virtual void SetHasSearchQuery(bool hasSearchQuery) = 0;
            };
        }
    }
}
