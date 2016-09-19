// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TagSearchSectionController.h"
#include "TagSearchAddedMessage.h"
#include "TagSearchRemovedMessage.h"
#include "TagSearchMenuOptionFactory.h"
#include "MenuOptionsModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            TagSearchSectionController::TagSearchSectionController(
                    Menu::View::IMenuOptionsModel& menuOptionsModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction)
            : m_menuOptionsModel(menuOptionsModel)
            , m_menuViewModel(menuViewModel)
            , m_messageBus(messageBus)
            , m_menuReaction(menuReaction)
            , m_tagSearchAddedMessageHandler(this, &TagSearchSectionController::OnTagSearchAddedMessage)
            , m_tagSearchRemovedMessageHandler(this, &TagSearchSectionController::OnTagSearchRemovedMessage)
            {
                m_messageBus.SubscribeUi(m_tagSearchAddedMessageHandler);
                m_messageBus.SubscribeUi(m_tagSearchRemovedMessageHandler);
            }

            TagSearchSectionController::~TagSearchSectionController()
            {
                m_messageBus.UnsubscribeUi(m_tagSearchAddedMessageHandler);
                m_messageBus.UnsubscribeUi(m_tagSearchRemovedMessageHandler);
            }

            void TagSearchSectionController::OnTagSearchAddedMessage(const TagSearch::TagSearchAddedMessage& message)
            {
                const auto& tagSearchModel = message.Model();

                if(!tagSearchModel.IsVisibleInSearchMenu())
                {
                    return;
                }

                auto* option = TagSearchMenuOptionFactory::CreateTagSearchMenuOption(
                        tagSearchModel,
                        m_menuViewModel,
                        m_messageBus,
                        m_menuReaction);

                const std::string details = "";

                m_menuOptionsModel.AddItem(
                        tagSearchModel.Name(),
                        tagSearchModel.Name(),
                        details,
                        tagSearchModel.Icon(),
                        option);
            }

            void TagSearchSectionController::OnTagSearchRemovedMessage(const TagSearch::TagSearchRemovedMessage& message)
            {
                m_menuOptionsModel.RemoveItem(message.Model().Name());
            }
        }
    }
}
