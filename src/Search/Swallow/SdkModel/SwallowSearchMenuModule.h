// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISwallowSearchMenuModule.h"
#include "Types.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchMenuModule : public ISwallowSearchMenuModule, private Eegeo::NonCopyable
                {
                public:
                    SwallowSearchMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~SwallowSearchMenuModule();
                    
                    Menu::View::IMenuModel& GetMeetingRoomsMenuModel() const;
                    Menu::View::IMenuModel& GetWorkingGroupsMenuModel() const;
                    Menu::View::IMenuModel& GetFacilitiesMenuModel() const;
                    Menu::View::IMenuModel& GetOfficesMenuModel() const;
                    
                private:
                    Menu::View::IMenuModel* m_pMeetingRoomsMenuModel;
                    Menu::View::IMenuOptionsModel* m_pMeetingRoomsMenuOptionsModel;
                    
                    Menu::View::IMenuModel* m_pWorkingGroupsMenuModel;
                    Menu::View::IMenuOptionsModel* m_pWorkingGroupsMenuOptionsModel;
                    
                    Menu::View::IMenuModel* m_pFacilitiesMenuModel;
                    Menu::View::IMenuOptionsModel* m_pFacilitiesMenuOptionsModel;
                    
                    Menu::View::IMenuModel* m_pOfficesMenuModel;
                    Menu::View::IMenuOptionsModel* m_pOfficesMenuOptionsModel;
                    
                    Menu::View::IMenuModel* m_pPersonMenuModel;
                    Menu::View::IMenuOptionsModel* m_pPersonsMenuOptionsModel;                    
                    
                };
            }
        }
    }
}