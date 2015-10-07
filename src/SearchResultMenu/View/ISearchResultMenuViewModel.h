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

                virtual void SetHasSearchQueryInFlight(bool hasSearchQueryInFlight) = 0;
                
                virtual void EnterAttractMode() = 0;
                
                virtual void ExitAttractMode() = 0;
                
                virtual bool AttractModeEnabled() const = 0;
                
                virtual void SetEnabled(bool enabled) = 0;
                
                virtual void InsertAttractModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void RemoveAttractModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
