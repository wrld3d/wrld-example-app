// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DirectionResultSectionViewModule.h"
namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace View
        {
            
            DirectionResultSectionViewModule::DirectionResultSectionViewModule(Menu::View::IMenuViewModel& directionMenuViewModel,
                                                                               Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               Menu::View::IMenuReactionModel& menuReaction,
                                                                               SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            {
                m_pDirectionController = Eegeo_NEW(DirectionResultSectionController)(directionMenuViewModel,menuOptionsModel,messageBus,menuReaction,searchResultPoiViewModel);
            }
            DirectionResultSectionViewModule::~DirectionResultSectionViewModule()
            {
                Eegeo_DELETE m_pDirectionController;
            }
            
        }
    }
}