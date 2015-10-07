// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "PerformedSearchMessage.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "CategorySearchSelectedMessage.h"
#include "WeatherSelectedMessage.h"
#include "PlaceJumpSelectedMessage.h"
#include "ModalityChangedMessage.h"
#include "FlattenButtonViewStateChangedMessage.h"
#include "CompassViewCycledMessage.h"
#include "SearchResultViewClearedMessage.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationViewSavePinMessage.h"
#include "MyPinDetailsViewRemovePinMessage.h"
#include "MyPinSelectedMessage.h"
#include "WorldPinsVisibilityMessage.h"
#include "UpdateNativeModalBackgroundMessage.h"
#include "StreamOverWifiOnlyChangedMessage.h"
#include "CacheEnabledChangedMessage.h"
#include "ClearCacheMessage.h"
#include "GpsMarkerVisibilityMessage.h"
#include "InitialExperienceIntroDismissedMessage.h"
#include "SearchResultPoiPinToggledMessage.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "InitialExperienceSearchResultAttractModeModelStateExitedMessage.h"
#include "TourActiveStateChangedMessage.h"
#include "ActiveTourQuitSelectedMessage.h"
#include "TourChangeRequestMessage.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorsExplorerExitMessage.h"
#include "MenuDragStateChangedMessage.h"
#include "CurrentTourCardTappedMessage.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        class UiToNativeMessageCatalog
            : public Eegeo::Messaging::CatalogBinding<SecondaryMenu::PerformedSearchMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultMenuItemSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<CategorySearch::CategorySearchSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<WeatherMenu::WeatherSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<PlaceJumps::PlaceJumpSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<Modality::ModalityChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Modality::UpdateNativeModalBackgroundMessage>
            , public Eegeo::Messaging::CatalogBinding<FlattenButton::FlattenButtonViewStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassViewCycledMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultViewClearedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinCreation::MyPinCreationViewStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinCreation::MyPinCreationViewSavePinMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinDetails::MyPinDetailsViewRemovePinMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPins::MyPinSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinsVisibilityMessage>
            , public Eegeo::Messaging::CatalogBinding<Options::StreamOverWifiOnlyChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Options::CacheEnabledChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Options::ClearCacheMessage>
            , public Eegeo::Messaging::CatalogBinding<GpsMarker::GpsMarkerVisibilityMessage>
        	, public Eegeo::Messaging::CatalogBinding<InitialExperience::InitialExperienceIntroDismissedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultPoi::SearchResultPoiPinToggledMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultPoi::SearchResultPoiViewOpenedMessage>
            , public Eegeo::Messaging::CatalogBinding<InitialExperience::SearchResultAttractMode::InitialExperienceSearchResultAttractModeModelStateExitedMessage>
            , public Eegeo::Messaging::CatalogBinding<Tours::TourActiveStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Tours::ActiveTourQuitSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<Tours::TourChangeRequestMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerSelectFloorMessage>
            , public Eegeo::Messaging::CatalogBinding<InteriorsExplorer::InteriorsExplorerExitMessage>
            , public Eegeo::Messaging::CatalogBinding<Menu::MenuDragStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Tours::CurrentTourCardTappedMessage>
            , private Eegeo::NonCopyable
        {

        };
    }
}
