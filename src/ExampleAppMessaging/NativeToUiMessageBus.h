// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "MessageBus.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryRemovedMessage.h"
#include "FlattenButtonModelStateChangedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "CompassModeCHangedMessage.h"
#include "CompassHeadingUpdateMessage.h"
#include "SearchResultGainedFocusMessage.h"
#include "SearchResultLostFocusMessage.h"
#include "SearchResultInFocusChangedLocationMessage.h"

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
        , public Eegeo::Messaging::CatalogBinding<SearchResultOnMap::SearchResultGainedFocusMessage>
        , public Eegeo::Messaging::CatalogBinding<SearchResultOnMap::SearchResultLostFocusMessage>
        , public Eegeo::Messaging::CatalogBinding<SearchResultOnMap::SearchResultInFocusChangedLocationMessage>
    	, private Eegeo::NonCopyable
    	{

    	};

    	typedef MessageBus<NativeToUiMessageCatalog> NativeToUiMessageBus;
    }
}
