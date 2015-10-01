// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultAddRemoveHandler.h"

#include "SearchVendorNames.h"
#include "SwallowSearchParser.h"
#include "SwallowOfficeResultMenuOption.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultAddRemoveHandler::SearchResultAddRemoveHandler(Menu::View::IMenuOptionsModel& menuOptions,
                                                                       Menu::View::IMenuViewModel& menuViewModel,
                                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : m_menuOptions(menuOptions)
            , m_menuViewModel(menuViewModel)
            , m_messageBus(messageBus)
            , m_handleSearchResultAddedMessageBinding(this, &SearchResultAddRemoveHandler::OnSearchResultAddedMessage)
            , m_handleSearchResultRemovedMessageBinding(this, &SearchResultAddRemoveHandler::OnSearchResultRemovedMessage)
            {
                m_messageBus.SubscribeUi(m_handleSearchResultAddedMessageBinding);
                m_messageBus.SubscribeUi(m_handleSearchResultRemovedMessageBinding);
            }
            
            SearchResultAddRemoveHandler::~SearchResultAddRemoveHandler()
            {
                m_messageBus.UnsubscribeUi(m_handleSearchResultAddedMessageBinding);
                m_messageBus.UnsubscribeUi(m_handleSearchResultRemovedMessageBinding);
            }
            
            void SearchResultAddRemoveHandler::OnSearchResultAddedMessage(const SearchResultAddedMessage& message)
            {
                const Search::SdkModel::SearchResultModel& model(message.Model());
                
                Menu::View::IMenuOption* menuOption = GetMenuOptionByVendor(model.GetVendor(), model);
                
                m_menuOptions.AddItem(model.GetIdentifier(),
                                      model.GetTitle(),
                                      model.GetSubtitle(),
                                      model.GetCategory(),
                                      menuOption);
            }
            
            void SearchResultAddRemoveHandler::OnSearchResultRemovedMessage(const SearchResultRemovedMessage& message)
            {
                const Search::SdkModel::SearchResultModel& model(message.Model());
                m_menuOptions.RemoveItem(model.GetIdentifier());
            }
            
            Menu::View::IMenuOption* SearchResultAddRemoveHandler::GetMenuOptionByVendor(const std::string& vendor, const Search::SdkModel::SearchResultModel model)
            {
                if(vendor == Search::SwallowOfficesVendorName)
                {
                    Search::Swallow::SdkModel::SwallowOfficeResultModel officeModel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowOfficeResult(model);
                    
                    return Eegeo_NEW(Search::Swallow::View::SwallowOfficeResultMenuOption)(officeModel.GetName(),
                                                                                           model.GetLocation(),
                                                                                           officeModel.GetHeadingDegrees(),
                                                                                           officeModel.GetDistance(),
                                                                                           m_menuViewModel,
                                                                                           m_messageBus);
                }
                else
                {
                    return Eegeo_NEW(SearchResultItemModel)(model.GetTitle(),
                                                                  model.GetLocation().ToECEF(),
                                                                  m_menuViewModel,
                                                                  m_messageBus);
                }
            }
        }
    }
}
