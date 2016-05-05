// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchMenuModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "LaxCategoryMenuOption.h"
#include "LaxSearchConstants.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxSearchMenuModule::LaxSearchMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                : m_pMeetingRoomsMenuModel(NULL)
                , m_pMeetingRoomsMenuOptionsModel(NULL)           
                {
                    m_pMeetingRoomsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pMeetingRoomsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMeetingRoomsMenuModel);
                    m_pMeetingRoomsMenuOptionsModel->AddItem("Defibrillator",
                                                             "Defibrillator",
                                                             "",
                                                             "",
                                                             Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::DEFIBRILLATOR_CATEGORY_NAME,
                                                                                                        true,
                                                                                                        menuViewModel,
                                                                                                        messageBus));
//                    
//                    m_pWorkingGroupsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
//                    m_pWorkingGroupsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pWorkingGroupsMenuModel);
//                    m_pWorkingGroupsMenuOptionsModel->AddItem("Working Groups",
//                                                              "Working Groups",
//                                                              "",
//                                                              "",
//                                                              Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME,
//                                                                                                         false,
//                                                                                                         menuViewModel,
//                                                                                                         static_cast<float>(Eegeo::Space::EarthConstants::Radius*2.0),
//                                                                                                         messageBus));
//                    
//                    m_pFacilitiesMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
//                    m_pFacilitiesMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pFacilitiesMenuModel);
//                    m_pFacilitiesMenuOptionsModel->AddItem("Facilities",
//                                                           "Facilities",
//                                                           "",
//                                                           "",
//                                                           Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME,
//                                                                                                      true,
//                                                                                                      menuViewModel,                                                                                                      messageBus));
//                    
//                    
//                    
//                    m_pPersonMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
//                    m_pPersonsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pPersonMenuModel);
//                    m_pPersonsMenuOptionsModel->AddItem("Person",
//                                                        "Person",
//                                                        "",
//                                                        "",
//                                                        Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME,                                                                                                      true,                                                                                                      menuViewModel,                                                                                                      messageBus));
//                                        
//                    
//                    m_pOfficesMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
//                    m_pOfficesMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOfficesMenuModel);
//                    m_pOfficesMenuOptionsModel->AddItem("Offices",
//                                                        "Offices",
//                                                        "",
//                                                        "",
//                                                        Eegeo_NEW(View::SwallowCategoryMenuOption)(Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME,
//                                                                                                   false,
//                                                                                                   menuViewModel,
//                                                                                                   static_cast<float>(Eegeo::Space::EarthConstants::Radius*2.0),
//                                                                                                   messageBus));
                }
                
                LaxSearchMenuModule::~LaxSearchMenuModule()
                {
//                    Eegeo_DELETE m_pOfficesMenuOptionsModel;
//                    
//                    Eegeo_DELETE m_pOfficesMenuModel;
//                    
//                    Eegeo_DELETE m_pFacilitiesMenuOptionsModel;
//                    
//                    Eegeo_DELETE m_pFacilitiesMenuModel;
//                    
//                    Eegeo_DELETE m_pWorkingGroupsMenuOptionsModel;
//                    
//                    Eegeo_DELETE m_pWorkingGroupsMenuModel;
                    
                    Eegeo_DELETE m_pMeetingRoomsMenuOptionsModel;
                    
                    Eegeo_DELETE m_pMeetingRoomsMenuModel;
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetMeetingRoomsMenuModel() const
                {
                    return *m_pMeetingRoomsMenuModel;
                }
                
//                Menu::View::IMenuModel& SwallowSearchMenuModule::GetWorkingGroupsMenuModel() const
//                {
//                    return *m_pWorkingGroupsMenuModel;
//                }
//                
//                Menu::View::IMenuModel& SwallowSearchMenuModule::GetFacilitiesMenuModel() const
//                {
//                    return *m_pFacilitiesMenuModel;
//                }
//                
//                Menu::View::IMenuModel& SwallowSearchMenuModule::GetOfficesMenuModel() const
//                {
//                    return *m_pOfficesMenuModel;
//                }
//                
//                Menu::View::IMenuModel& SwallowSearchMenuModule::GetPersonMenuModel() const
//                {
//                    return *m_pPersonMenuModel;
//                }
            }
        }
    }
}
