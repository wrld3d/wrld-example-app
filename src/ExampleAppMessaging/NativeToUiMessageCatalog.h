// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryRemovedMessage.h"
#include "FlattenButtonModelStateChangedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "CompassModeCHangedMessage.h"
#include "CompassHeadingUpdateMessage.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"
#include "MyPinCreationStateChangedMessage.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "UserCreatedMyPinDetailsModelSelectedMessage.h"
#include "SearchResultMyPinDetailsModelSelectedMessage.h"
#include "MyPinAddedToMenuMessage.h"
#include "MyPinRemovedFromMenuMessage.h"
#include "ShowInitialExperienceDialogMessage.h"
#include "CompletedCacheClearMessage.h"
#include "SearchResultPoiViewImageDownloadCompletedMessage.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        class NativeToUiMessageCatalog
            : public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultAddedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryPerformedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryRemovedMessage>
            , public Eegeo::Messaging::CatalogBinding<FlattenButton::FlattenButtonModelStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Search::SearchQueryResponseReceivedMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassModeChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<Compass::CompassHeadingUpdateMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinGainedFocusMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinLostFocusMessage>
            , public Eegeo::Messaging::CatalogBinding<WorldPins::WorldPinInFocusChangedLocationMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinCreation::MyPinCreationStateChangedMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultOnMap::SearchResultOnMapItemModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinDetails::UserCreatedMyPinDetailsModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPinDetails::SearchResultMyPinDetailsModelSelectedMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPins::MyPinAddedToMenuMessage>
            , public Eegeo::Messaging::CatalogBinding<MyPins::MyPinRemovedFromMenuMessage>
        	, public Eegeo::Messaging::CatalogBinding<InitialExperience::Dialogs::ShowInitialExperienceDialogMessage>
            , public Eegeo::Messaging::CatalogBinding<Options::CompletedCacheClearMessage>
            , public Eegeo::Messaging::CatalogBinding<SearchResultPoi::SearchResultPoiViewImageDownloadCompletedMessage>
            , private Eegeo::NonCopyable
        {

        };
    }
}
