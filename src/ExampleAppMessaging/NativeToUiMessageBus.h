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
    	: public CatalogBinding<SearchResultMenu::SearchResultAddedMessage>
    	, public CatalogBinding<SearchResultMenu::SearchResultRemovedMessage>
    	, public CatalogBinding<Search::SearchQueryPerformedMessage>
        , public CatalogBinding<Search::SearchQueryRemovedMessage>
        , public CatalogBinding<FlattenButton::FlattenButtonModelStateChangedMessage>
    	, public CatalogBinding<Search::SearchQueryResponseReceivedMessage>
        , public CatalogBinding<Compass::CompassModeChangedMessage>
        , public CatalogBinding<Compass::CompassHeadingUpdateMessage>
        , public CatalogBinding<SearchResultOnMap::SearchResultGainedFocusMessage>
        , public CatalogBinding<SearchResultOnMap::SearchResultLostFocusMessage>
        , public CatalogBinding<SearchResultOnMap::SearchResultInFocusChangedLocationMessage>
    	, private Eegeo::NonCopyable
    	{

    	};

    	typedef MessageBus<NativeToUiMessageCatalog> NativeToUiMessageBus;
    }
}
