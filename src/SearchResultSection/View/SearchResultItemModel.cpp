// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultItemModel.h"

#include "SearchResultSectionItemSelectedMessage.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            SearchResultItemModel::SearchResultItemModel(const std::string& name,
                                                         const Eegeo::dv3& searchResultModelLocationEcef,
                                                         const bool isInterior,
                                                         const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                         const int floorIndex,
                                                         const std::string modelIdentifier,
                                                         OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                                         SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                                         int itemIndex,
                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                         const Menu::View::IMenuReactionModel& menuReaction)
            : m_name(name)
            , m_searchResultModelLocationEcef(searchResultModelLocationEcef)
            , m_isInterior(isInterior)
            , m_interiorId(interiorId)
            , m_floorIndex(floorIndex)
            , m_modelIdentifier(modelIdentifier)
            , m_searchMenuViewModel(searchMenuViewModel)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_messageBus(messageBus)
            , m_itemIndex(itemIndex)
            , m_menuReaction(menuReaction)
            {

            }

            SearchResultItemModel::~SearchResultItemModel()
            {

            }

            void SearchResultItemModel::Select()
            {
                if (m_menuReaction.GetShouldCloseMenu())
                {
                    m_searchMenuViewModel.Close();
                }

                if (m_searchResultPoiViewModel.IsOpen())
                {
                    m_searchResultPoiViewModel.Close();
                }

                m_messageBus.Publish(SearchResultSectionItemSelectedMessage(m_searchResultModelLocationEcef,
                                                                            m_isInterior,
                                                                            m_interiorId,
                                                                            m_floorIndex,
                                                                            m_itemIndex,
                                                                            m_modelIdentifier));
            }
        }
    }
}
