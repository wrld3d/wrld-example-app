// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchMenuModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SwallowCategoryMenuOption.h"
#include "SwallowSearchConstants.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchMenuModule::SwallowSearchMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                : m_pMeetingRoomsMenuModel(NULL)
                , m_pMeetingRoomsMenuOptionsModel(NULL)
                , m_pWorkingGroupsMenuModel(NULL)
                , m_pWorkingGroupsMenuOptionsModel(NULL)
                , m_pOfficesMenuModel(NULL)
                , m_pOfficesMenuOptionsModel(NULL)
                , m_pFacilitiesMenuModel(NULL)
                , m_pFacilitiesMenuOptionsModel(NULL)
                {
                    m_pMeetingRoomsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pMeetingRoomsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMeetingRoomsMenuModel);
                    m_pMeetingRoomsMenuOptionsModel->AddItem("Meeting Rooms",
                                                             "Meeting Rooms",
                                                             "",
                                                             "",
                                                             Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME,
                                                                                                        true,
                                                                                                        true,
                                                                                                        menuViewModel,
                                                                                                        messageBus));
                    
                    m_pWorkingGroupsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pWorkingGroupsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pWorkingGroupsMenuModel);
                    m_pWorkingGroupsMenuOptionsModel->AddItem("Working Groups",
                                                              "Working Groups",
                                                              "",
                                                              "",
                                                              Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME,
                                                                                                         false,
                                                                                                         true,
                                                                                                         menuViewModel,
                                                                                                         static_cast<float>(Eegeo::Space::EarthConstants::Radius*2.0),
                                                                                                         messageBus));
                    
                    m_pFacilitiesMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pFacilitiesMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pFacilitiesMenuModel);
                    m_pFacilitiesMenuOptionsModel->AddItem("Facilities",
                                                           "Facilities",
                                                           "",
                                                           "",
                                                           Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME,
                                                                                                      true,
                                                                                                      true,
                                                                                                      menuViewModel,
                                                                                                      messageBus));
                    
                    m_pOfficesMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pOfficesMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOfficesMenuModel);
                    m_pOfficesMenuOptionsModel->AddItem("Offices",
                                                        "Offices",
                                                        "",
                                                        "",
                                                        Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME,
                                                                                                   false,
                                                                                                   false,
                                                                                                   menuViewModel,
                                                                                                   static_cast<float>(Eegeo::Space::EarthConstants::Radius*2.0),
                                                                                                   messageBus));
                }
                
                SwallowSearchMenuModule::~SwallowSearchMenuModule()
                {
                    Eegeo_DELETE m_pOfficesMenuOptionsModel;
                    
                    Eegeo_DELETE m_pOfficesMenuModel;
                    
                    Eegeo_DELETE m_pFacilitiesMenuOptionsModel;
                    
                    Eegeo_DELETE m_pFacilitiesMenuModel;
                    
                    Eegeo_DELETE m_pWorkingGroupsMenuOptionsModel;
                    
                    Eegeo_DELETE m_pWorkingGroupsMenuModel;
                    
                    Eegeo_DELETE m_pMeetingRoomsMenuOptionsModel;
                    
                    Eegeo_DELETE m_pMeetingRoomsMenuModel;
                }
                
                Menu::View::IMenuModel& SwallowSearchMenuModule::GetMeetingRoomsMenuModel() const
                {
                    return *m_pMeetingRoomsMenuModel;
                }
                
                Menu::View::IMenuModel& SwallowSearchMenuModule::GetWorkingGroupsMenuModel() const
                {
                    return *m_pWorkingGroupsMenuModel;
                }
                
                Menu::View::IMenuModel& SwallowSearchMenuModule::GetFacilitiesMenuModel() const
                {
                    return *m_pFacilitiesMenuModel;
                }
                
                Menu::View::IMenuModel& SwallowSearchMenuModule::GetOfficesMenuModel() const
                {
                    return *m_pOfficesMenuModel;
                }
            }
        }
    }
}
