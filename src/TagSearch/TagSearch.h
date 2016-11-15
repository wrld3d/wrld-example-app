// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class ITagSearchModule;
            class ITagIconMapper;
        }

        namespace View
        {
            class ITagSearchModel;
            class ITagSearchRepository;
            class TagSearchSectionController;
            class TagSearchMenuOption;
        }
        
        class ISearchResultIconKeyMapper;
        class TagSearchAddedMessage;
        class TagSearchRemovedMessage;
    }
}
