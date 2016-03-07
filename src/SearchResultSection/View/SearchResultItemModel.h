// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include <string>

#include "BidirectionalBus.h"
#include "Interiors.h"
#include "IOpenableControlViewModel.h"
#include "Types.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace SearchResultSection
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
                
                int m_itemIndex;

            public:
                SearchResultItemModel(const std::string& name,
                                      const Eegeo::dv3& searchResultModelLocationEcef,
                                      const bool isInterior,
                                      const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                      const int floorIndex,
                                      OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                      int itemIndex,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultItemModel();

                void Select();
            };
        }
    }

}
