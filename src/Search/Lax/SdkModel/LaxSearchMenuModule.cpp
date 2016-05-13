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
                : m_pDefibrillatorMenuModel(NULL)
                , m_pDefibrillatorMenuOptionsModel(NULL)
                {
                    m_pDefibrillatorMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pDefibrillatorMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pDefibrillatorMenuModel);
                    m_pDefibrillatorMenuOptionsModel->AddItem("Defibrillator",
                                                             "Defibrillator",
                                                             "",
                                                             "",
                                                             Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::DEFIBRILLATOR_CATEGORY_NAME,
                                                                                                        true,
                                                                                                        menuViewModel,
                                                                                                        messageBus));
                    
                    m_pFoodMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pFoodMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pFoodMenuModel);
                    m_pFoodMenuOptionsModel->AddItem("Food",
                                                             "Food",
                                                             "",
                                                             "",
                                                             Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::FOOD_CATEGORY_NAME,
                                                                                                    true,
                                                                                                    menuViewModel,
                                                                                                    messageBus));
                    

                    m_pShoppingMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pShoppingMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pShoppingMenuModel);
                    m_pShoppingMenuOptionsModel->AddItem("Shopping",
                                                     "Shopping",
                                                     "",
                                                     "",
                                                     Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::SHOPPING_CATEGORY_NAME,
                                                                                            true,
                                                                                            menuViewModel,
                                                                                            messageBus));

                    m_pElevatorMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pElevatorMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pElevatorMenuModel);
                    m_pElevatorMenuOptionsModel->AddItem("Elevator",
                                                         "Elevator",
                                                         "",
                                                         "",
                                                         Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::ELEVATOR_CATEGORY_NAME,
                                                                                                true,
                                                                                                menuViewModel,
                                                                                                messageBus));
                    
                    m_pStairsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pStairsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pStairsMenuModel);
                    m_pStairsMenuOptionsModel->AddItem("Stairs",
                                                         "Stairs",
                                                         "",
                                                         "",
                                                         Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::STAIRS_CATEGORY_NAME,
                                                                                                true,
                                                                                                menuViewModel,
                                                                                                messageBus));

                    m_pEscalatorMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pEscalatorMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pEscalatorMenuModel);
                    m_pEscalatorMenuOptionsModel->AddItem("Escalator",
                                                       "Escalator",
                                                       "",
                                                       "",
                                                       Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::ESCALATOR_CATEGORY_NAME,
                                                                                              true,
                                                                                              menuViewModel,
                                                                                              messageBus));

                    
                    
                    m_pRestroomMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pRestroomMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pRestroomMenuModel);
                    m_pRestroomMenuOptionsModel->AddItem("Restroom",
                                                       "Restroom",
                                                       "",
                                                       "",
                                                       Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::RESTROOM_CATEGORY_NAME,
                                                                                              true,
                                                                                              menuViewModel,
                                                                                              messageBus));
                    
                    m_pTddpayphoneMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pTddpayphoneMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pTddpayphoneMenuModel);
                    m_pTddpayphoneMenuOptionsModel->AddItem("Tddpayphone",
                                                         "Tddpayphone",
                                                         "",
                                                         "",
                                                         Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::TDD_PAYPHONE_CATEGORY_NAME,
                                                                                                true,
                                                                                                menuViewModel,
                                                                                                messageBus));

                    m_pAtmMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pAtmMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pAtmMenuModel);
                    m_pAtmMenuOptionsModel->AddItem("Atm",
                                                            "Atm",
                                                            "",
                                                            "",
                                                            Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::ATM_CATEGORY_NAME,
                                                                                                   true,
                                                                                                   menuViewModel,
                                                                                                   messageBus));

                    m_pPayphoneMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pPayphoneMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pPayphoneMenuModel);
                    m_pPayphoneMenuOptionsModel->AddItem("Payphone",
                                                    "Payphone",
                                                    "",
                                                    "",
                                                    Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::PAYPHONE_CATEGORY_NAME,
                                                                                           true,
                                                                                           menuViewModel,
                                                                                           messageBus));

                    m_pGatesMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pGatesMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pGatesMenuModel);
                    m_pGatesMenuOptionsModel->AddItem("Gates",
                                                         "Gates",
                                                         "",
                                                         "",
                                                         Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::GATES_CATEGORY_NAME,
                                                                                                true,
                                                                                                menuViewModel,
                                                                                                messageBus));
                    
                    m_pOthersMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                    m_pOthersMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOthersMenuModel);
                    m_pOthersMenuOptionsModel->AddItem("Others",
                                                      "Others",
                                                      "",
                                                      "",
                                                      Eegeo_NEW(View::LaxCategoryMenuOption)(Search::Lax::SearchConstants::OTHERS_CATEGORY_NAME,
                                                                                             true,
                                                                                             menuViewModel,
                                                                                             messageBus));

                }
                
                LaxSearchMenuModule::~LaxSearchMenuModule()
                {
                    
                    Eegeo_DELETE m_pDefibrillatorMenuOptionsModel;
                    
                    Eegeo_DELETE m_pDefibrillatorMenuModel;
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetDefibrillatorMenuModel() const
                {
                    return *m_pDefibrillatorMenuModel;
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetFoodMenuModel() const
                {
                    return *m_pFoodMenuModel;
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetShoppingMenuModel() const
                {
                    return *m_pShoppingMenuModel;
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetElevatorMenuModel() const
                {
                    return *m_pElevatorMenuModel;
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetStairsMenuModel() const
                {
                    return *m_pStairsMenuModel;
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetEscalatorMenuModel() const
                {
                    return *m_pEscalatorMenuModel;
                }

                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetRestroomMenuModel() const
                {
                    
                    return *m_pRestroomMenuModel;
                    
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetTddpayphoneMenuModel() const
                {
                    
                    return *m_pTddpayphoneMenuModel;
                    
                }

                Menu::View::IMenuModel& LaxSearchMenuModule::GetAtmMenuModel() const
                {
                    
                    return *m_pAtmMenuModel;
                    
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetPayphoneMenuModel() const
                {
                    
                    return *m_pPayphoneMenuModel;
                    
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetGateseMenuModel() const
                {
                    return *m_pGatesMenuModel;
                    
                }
                
                Menu::View::IMenuModel& LaxSearchMenuModule::GetOthersMenuModel() const
                {
                    return *m_pOthersMenuModel;
                }

            }
        }
    }
}
