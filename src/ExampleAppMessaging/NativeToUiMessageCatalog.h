// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "Types.h"
#include "CatalogBinding.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryRefreshedMessage.h"
#include "SearchQueryRequestMessage.h"
#include "SearchQueryRemovedMessage.h"
#include "SearchQueryResultsRemovedMessage.h"
#include "AutocompleteSuggestionsReceivedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "SearchQueryClearRequestMessage.h"
#include "CompassModeChangedMessage.h"
#include "CompassHeadingUpdateMessage.h"
#include "CompassModeUnauthorizedMessage.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"
#include "MyPinCreationStateChangedMessage.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "UserCreatedMyPinDetailsModelSelectedMessage.h"
#include "SearchResultMyPinDetailsModelSelectedMessage.h"
#include "MyPinAddedToMenuMessage.h"
#include "MyPinRemovedFromMenuMessage.h"
#include "ShowInitialExperienceIntroMessage.h"
#include "CompletedCacheClearMessage.h"
#include "SearchResultPoiViewImageDownloadCompletedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"
#include "InteriorsExplorerInteriorStreamingMessage.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "WatermarkModelChangedMessage.h"
#include "WatermarkAlignmentStateChangedMessage.h"
#include "WatermarkInteriorStylingStateChangedMessage.h"
#include "SetWatermarkVisibilityMessage.h"
#include "AppModeChangedMessage.h"
#include "UserInteractionEnabledChangedMessage.h"
#include "URLRequestedMessage.h"
#include "DeeplinkURLRequestedMessage.h"
#include "ConnectivityChangedViewMessage.h"
#include "StartUxSurveyMessage.h"
#include "InteriorsExplorerUINotifyMessage.h"
#include "TagSearchAddedMessage.h"
#include "TagSearchRemovedMessage.h"
#include "VirtualKeyboardStateChangedMessage.h"
#include "AboutPageIndoorPositionTypeMessage.h"
#include "AboutPageIndoorAtlasDataMessage.h"
#include "AttractModeStateChangedMessage.h"
#include "AboutPageSenionDataMessage.h"
#include "AboutPageIndoorPositionSettingsMessage.h"
#include "OpenSearchMenuMessage.h"
#include "CompassIsRotatingStateChangedMessage.h"
#include "SelectMenuItemMessage.h"
#include "ClosePoiMessage.h"
#include "OpenSearchMenuSectionMessage.h"
#include "NavRoutingViewOpenMessage.h"
#include "NavRoutingStartLocationSetMessage.h"
#include "NavRoutingStartLocationClearedMessage.h"
#include "NavRoutingEndLocationSetMessage.h"
#include "NavRoutingEndLocationClearedMessage.h"
#include "NavRoutingRouteChangedMessage.h"
#include "NavRoutingRouteClearedMessage.h"
#include "NavRoutingCurrentDirectionSetMessage.h"
#include "NavRoutingCurrentDirectionUpdatedMessage.h"
#include "NavRoutingSelectedDirectionSetMessage.h"
#include "NavRoutingRemainingRouteDurationSetMessage.h"
#include "NavRoutingModeSetMessage.h"
#include "NavRoutingShowRerouteDialogMessage.h"
#include "NavRoutingSetCalculatingRouteMessage.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        class NativeToUiMessageCatalog
            : public Eegeo::Messaging::CatalogBinding<TagSearch::TagSearchAddedMessage>
            , public Eegeo::Messaging::CatalogBinding<TagSearch::TagSearchRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultSection::SearchResultAddedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultSection::SearchResultRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryPerformedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryRequestMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryRefreshedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryResultsRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryResponseReceivedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryClearRequestMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::AutocompleteSuggestionsReceivedMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassModeChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassHeadingUpdateMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassModeUnauthorizedMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinGainedFocusMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinLostFocusMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinInFocusChangedLocationMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinCreation::MyPinCreationStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultOnMap::SearchResultOnMapItemModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinDetails::UserCreatedMyPinDetailsModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinDetails::SearchResultMyPinDetailsModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPins::MyPinAddedToMenuMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPins::MyPinRemovedFromMenuMessage>
        	, public Eegeo::Messaging::CatalogBinding<InitialExperience::ShowInitialExperienceIntroMessage>
            , public Eegeo::Messaging::CatalogBinding<Options::CompletedCacheClearMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultPoi::SearchResultPoiViewImageDownloadCompletedMessage>
            , public Eegeo::Messaging::CatalogBinding<Watermark::SetWatermarkVisibilityMessage>
            , public Eegeo::Messaging::CatalogBinding<Watermark::WatermarkModelChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Watermark::WatermarkAlignmentStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Watermark::WatermarkInteriorStylingStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerFloorSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerInteriorStreamingMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<AppModes::AppModeChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<UserInteraction::UserInteractionEnabledChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<URLRequest::URLRequestedMessage>
            , public Eegeo::Messaging::CatalogBinding<URLRequest::DeeplinkURLRequestedMessage>
            , public Eegeo::Messaging::CatalogBinding<Net::ConnectivityChangedViewMessage>
            , public Eegeo::Messaging::CatalogBinding<Surveys::StartUxSurveyMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerUINotifyMessage>
            , public Eegeo::Messaging::CatalogBinding<VirtualKeyboard::VirtualKeyboardStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<AboutPage::AboutPageIndoorPositionTypeMessage>
            , public Eegeo::Messaging::CatalogBinding<AboutPage::AboutPageSenionDataMessage>
            , public Eegeo::Messaging::CatalogBinding<AboutPage::AboutPageIndoorAtlasDataMessage>
            , public Eegeo::Messaging::CatalogBinding<AboutPage::AboutPageIndoorPositionSettingsMessage>
            , public Eegeo::Messaging::CatalogBinding<AttractMode::AttractModeStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchMenu::OpenSearchMenuMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassIsRotatingStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Automation::SelectMenuItemMessage>
            , public Eegeo::Messaging::CatalogBinding<Automation::ClosePoiMessage>
            , public Eegeo::Messaging::CatalogBinding<Automation::OpenSearchMenuSectionMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingViewOpenMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingStartLocationSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingStartLocationClearedMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingEndLocationSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingEndLocationClearedMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingRouteChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingRouteClearedMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingCurrentDirectionSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingCurrentDirectionUpdatedMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingSelectedDirectionSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingRemainingRouteDurationSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingModeSetMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingShowRerouteDialogMessage>
            , public Eegeo::Messaging::CatalogBinding<NavRouting::NavRoutingSetCalculatingRouteMessage>
            , private Eegeo::NonCopyable
        {

        };
    }
}
