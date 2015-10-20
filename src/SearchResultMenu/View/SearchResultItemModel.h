// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IMenuOption.h"
#include "Search.h"
#include "CameraTransitions.h"
#include "IOpenableControlViewModel.h"
#include "VectorMath.h"
#include "BidirectionalBus.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultItemModel: public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                std::string m_name;
                Eegeo::dv3 m_searchResultModelLocationEcef;
                bool m_isInterior;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_floorIndex;
                OpenableControl::View::IOpenableControlViewModel& m_searchMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                SearchResultItemModel(const std::string& name,
                                      const Eegeo::dv3& searchResultModelLocationEcef,
                                      const bool isInterior,
                                      const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                      const int floorIndex,
                                      OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultItemModel();

                void Select();
            };
        }
    }

}
