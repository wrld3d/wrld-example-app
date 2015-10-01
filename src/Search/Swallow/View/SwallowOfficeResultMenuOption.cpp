// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowOfficeResultMenuOption.h"

#include "SwallowOfficeResultMenuOptionSelectedMessage.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace View
            {
                SwallowOfficeResultMenuOption::SwallowOfficeResultMenuOption(const std::string& name,
                                                                             const Eegeo::Space::LatLong& location,
                                                                             float headingDegrees,
                                                                             float distance,
                                                                             OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                                                             ExampleAppMessaging::TMessageBus& messageBus)
                : m_name(name)
                , m_location(location)
                , m_headingDegrees(headingDegrees)
                , m_distance(distance)
                , m_searchMenuViewModel(searchMenuViewModel)
                , m_messageBus(messageBus)
                {
                    
                }
                
                SwallowOfficeResultMenuOption::~SwallowOfficeResultMenuOption()
                {
                    
                }
                
                void SwallowOfficeResultMenuOption::Select()
                {
                    m_searchMenuViewModel.Close();
                    
                    m_messageBus.Publish(SwallowOfficeResultMenuOptionSelectedMessage(m_location, m_headingDegrees, m_distance));
                }
            }
        }
    }
}
