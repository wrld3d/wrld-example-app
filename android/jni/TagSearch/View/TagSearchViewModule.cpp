// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchViewModule.h"
#include "TagSearchSectionController.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            TagSearchViewModule* TagSearchViewModule::Create(
                    Menu::View::IMenuOptionsModel& menuOptionsModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction)
            {
                auto* pController = Eegeo_NEW(TagSearch::View::TagSearchSectionController)(
                        menuOptionsModel,
                        menuViewModel,
                        messageBus,
                        menuReaction);

                return Eegeo_NEW(TagSearchViewModule)(pController);
            }

            TagSearchViewModule::TagSearchViewModule(TagSearch::View::TagSearchSectionController* pController)
            : m_pController(pController)
            {

            }

            TagSearchViewModule::~TagSearchViewModule()
            {
                Eegeo_DELETE m_pController;
            }
        }
    }
}
