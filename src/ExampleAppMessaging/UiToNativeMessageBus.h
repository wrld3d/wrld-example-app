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
			: public Eegeo::Messaging::CatalogBinding<SecondaryMenu::PerformedSearchMessage>
			, public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultMenuItemSelectedMessage>
			, public Eegeo::Messaging::CatalogBinding<CategorySearch::CategorySearchSelectedMessage>
			, public Eegeo::Messaging::CatalogBinding<WeatherMenu::WeatherSelectedMessage>
			, public Eegeo::Messaging::CatalogBinding<PlaceJumps::PlaceJumpSelectedMessage>
			, public Eegeo::Messaging::CatalogBinding<Modality::ModalityChangedMessage>
			, public Eegeo::Messaging::CatalogBinding<FlattenButton::FlattenButtonViewStateChangedMessage>
			, public Eegeo::Messaging::CatalogBinding<Compass::CompassViewCycledMessage>
			, public Eegeo::Messaging::CatalogBinding<SearchResultMenu::SearchResultViewClearedMessage>
			, private Eegeo::NonCopyable
		{

		};

		typedef MessageBus<UiToNativeMessageCatalog> UiToNativeMessageBus;
	}
}
