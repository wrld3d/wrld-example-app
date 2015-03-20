// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "SearchResultPinAddedEvent.h"
#include "SearchResultPinRemovedEvent.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        class SdkDomainEventsMessageCatalog
        : public Eegeo::Messaging::CatalogBinding<MyPins::SdkModel::SearchResultPinAddedEvent>
        , public Eegeo::Messaging::CatalogBinding<MyPins::SdkModel::SearchResultPinRemovedEvent>
        , private Eegeo::NonCopyable
        {
            
        };
    }
}
