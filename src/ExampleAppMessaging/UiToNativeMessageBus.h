// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "MessageBus.h"
#include "PerformedSearchMessage.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "CategorySearchSelectedMessage.h"
#include "WeatherSelectedMessage.h"
#include "PlaceJumpSelectedMessage.h"
#include "ModalityChangedMessage.h"
#include "FlattenButtonViewStateChangedMessage.h"
#include "CompassViewCycledMessage.h"
#include "SearchResultViewClearedMessage.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
    	class UiToNativeMessageCatalog
    	: public CatalogBinding<SecondaryMenu::PerformedSearchMessage>
    	, public CatalogBinding<SearchResultMenu::SearchResultMenuItemSelectedMessage>
    	, public CatalogBinding<CategorySearch::CategorySearchSelectedMessage>
    	, public CatalogBinding<WeatherMenu::WeatherSelectedMessage>
        , public CatalogBinding<PlaceJumps::PlaceJumpSelectedMessage>
        , public CatalogBinding<Modality::ModalityChangedMessage>
        , public CatalogBinding<FlattenButton::FlattenButtonViewStateChangedMessage>
        , public CatalogBinding<Compass::CompassViewCycledMessage>
        , public CatalogBinding<SearchResultMenu::SearchResultViewClearedMessage>
    	, private Eegeo::NonCopyable
    	{
            
    	};

    	typedef MessageBus<UiToNativeMessageCatalog> UiToNativeMessageBus;
    }
}
