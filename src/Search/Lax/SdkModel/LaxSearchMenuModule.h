// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ILaxSearchMenuModule.h"
#include "Types.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxSearchMenuModule : public ILaxSearchMenuModule, private Eegeo::NonCopyable
                {
                public:
                    LaxSearchMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~LaxSearchMenuModule();
                    
                    Menu::View::IMenuModel& GetMeetingRoomsMenuModel() const;
//                  Menu::View::IMenuModel& GetWorkingGroupsMenuModel() const;
//                  Menu::View::IMenuModel& GetFacilitiesMenuModel() const;
//                  Menu::View::IMenuModel& GetOfficesMenuModel() const;
//                  Menu::View::IMenuModel& GetPersonMenuModel() const;     // new //
                    
                private:
                    Menu::View::IMenuModel* m_pMeetingRoomsMenuModel;
                    Menu::View::IMenuOptionsModel* m_pMeetingRoomsMenuOptionsModel;
                    
//                  Menu::View::IMenuModel* m_pWorkingGroupsMenuModel;
//                  Menu::View::IMenuOptionsModel* m_pWorkingGroupsMenuOptionsModel;
//                    
//                  Menu::View::IMenuModel* m_pFacilitiesMenuModel;
//                  Menu::View::IMenuOptionsModel* m_pFacilitiesMenuOptionsModel;
//                    
//                  Menu::View::IMenuModel* m_pOfficesMenuModel;
//                  Menu::View::IMenuOptionsModel* m_pOfficesMenuOptionsModel;
                    
//                    // new //
//                  Menu::View::IMenuModel* m_pPersonMenuModel;
//                  Menu::View::IMenuOptionsModel* m_pPersonsMenuOptionsModel;
                    
                };
            }
        }
    }
}