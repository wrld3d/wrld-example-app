// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultItemModel.h"
#include "SearchResultModel.h"
#include "ICameraTransitionController.h"
#include "Logger.h"
#include "SearchResultMenuItemSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultItemModel::SearchResultItemModel(const std::string& name,
                                                         const Eegeo::dv3& searchResultModelLocationEcef,
                                                         const bool isInterior,
                                                         const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                         const int floorIndex,
                                                         OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
            : m_name(name)
            , m_searchResultModelLocationEcef(searchResultModelLocationEcef)
            , m_isInterior(isInterior)
            , m_interiorId(interiorId)
            , m_floorIndex(floorIndex)
            , m_searchMenuViewModel(searchMenuViewModel)
            , m_messageBus(messageBus)
            {

            }

            SearchResultItemModel::~SearchResultItemModel()
            {

            }

            void SearchResultItemModel::Select()
            {
                m_searchMenuViewModel.Close();

                m_messageBus.Publish(SearchResultMenuItemSelectedMessage(m_searchResultModelLocationEcef,
                                                                         m_isInterior,
                                                                         m_interiorId,
                                                                         m_floorIndex));
            }
        }
    }
}
