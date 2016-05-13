// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include <string>

#include "Types.h"

#include "BidirectionalBus.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace View
            {
                class LaxOfficeResultMenuOption: public Menu::View::IMenuOption, private Eegeo::NonCopyable
                {
                    std::string m_name;
                    Eegeo::Space::LatLong m_location;
                    float m_headingDegrees;
                    float m_distance;
                    OpenableControl::View::IOpenableControlViewModel& m_searchMenuViewModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                public:
                    LaxOfficeResultMenuOption(const std::string& name,
                                                  const Eegeo::Space::LatLong& location,
                                                  float headingDegrees,
                                                  float distance,
                                                  OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~LaxOfficeResultMenuOption();
                    
                    void Select();
                };
            }
        }
    }
}
