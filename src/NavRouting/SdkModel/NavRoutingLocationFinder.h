#pragma once

#include "Types.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "INavRoutingLocationFinder.h"
#include "NavRoutingLocationModel.h"
#include "SearchResultModel.h"
#include "ILocationService.h"
#include "IAlertBoxFactory.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingLocationFinder : public INavRoutingLocationFinder, private Eegeo::NonCopyable
            {
            private:
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<NavRoutingLocationFinder> m_failAlertHandler;

                void OnFailAlertBoxDismissed();

            public:
                NavRoutingLocationFinder(
                        Eegeo::Location::ILocationService& locationService,
                        Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                        Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);
                
                virtual ~NavRoutingLocationFinder() {};
                
                bool TryGetCurrentLocation(NavRoutingLocationModel &outLocation);
                bool TryGetLocationFromSearchResultModel(
                        const Search::SdkModel::SearchResultModel& searchResultModel,
                        NavRoutingLocationModel &outLocation);
            };
        }
    }
}
