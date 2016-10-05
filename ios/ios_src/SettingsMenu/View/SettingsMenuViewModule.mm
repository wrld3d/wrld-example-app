// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuViewModule.h"
#include "SettingsMenuModule.h"
#include "SettingsMenuView.h"
#include "SettingsMenu.h"
#include "ScreenProperties.h"
#include "MenuViewInterop.h"
#include "SettingsMenuViewInterop.h"
#include "SettingsMenuController.h"
#include "SettingsTableDataProvider.h"
#include "IModalBackgroundView.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            void SettingsMenuViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto provider = [SettingsTableDataProvider alloc];
                                                     return std::make_shared<SettingsTableDataProviderWrapper>(provider);
                                                 }).singleInstance();
                
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto provider = context.resolve<SettingsTableDataProviderWrapper>();
                                                     auto viewModel = context.resolve<SettingsMenuViewModel>();
                                                     auto view = [[SettingsMenuView alloc] initWithParams
                                                                :screenProperties->GetScreenWidth()
                                                                :screenProperties->GetScreenHeight()
                                                                :screenProperties->GetPixelScale()
                                                                :provider->Get()
                                                                :static_cast<int>(viewModel->SectionsCount())];
                                                     return std::make_shared<SettingsMenuViewWrapper>(view);
                                                 }).singleInstance();
                
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<SettingsMenuViewWrapper>();
                                                     auto interop = [view->Get() getSettingsMenuInterop];
                                                     return Hypodermic::makeExternallyOwned(*interop);
                                                 }).as<ISettingsMenuView>().singleInstance();
                
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<SettingsMenuViewWrapper>();
                                                     auto menuInterop = [view->Get() getInterop];
                                                     return std::make_shared<SettingsMenuController>(
                                                                                            Hypodermic::makeExternallyOwned(*menuInterop),
                                                                                            context.resolve<SettingsMenuModel>(),
                                                                                            context.resolve<SettingsMenuViewModel>(),
                                                                                            context.resolve<Modality::View::IModalBackgroundView>(),
                                                                                            context.resolve<ExampleAppMessaging::TMessageBus>()
                                                     );
                                                 }).singleInstance();
            }
            
            void SettingsMenuViewModule::RegisterUiLeaves()
            {
                RegisterLeaf<SettingsMenuController>();
            }
            
            /*
            SettingsMenuViewModule::SettingsMenuViewModule(Menu::View::IMenuModel& settingsMenuModel,
                                                           Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            {
                builder->registerI
                m_pDataProvider = [SettingsTableDataProvider alloc];

                m_pView = [[SettingsMenuView alloc] initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :m_pDataProvider
                           :static_cast<int>(settingsMenuViewModel.SectionsCount())];

                m_pController = Eegeo_NEW(SettingsMenuController)(*[m_pView getInterop],
                                                                  settingsMenuModel,
                                                                  settingsMenuViewModel,
                                                                  modalBackgroundView,
                                                                  messageBus);
            }

            SettingsMenuViewModule::~SettingsMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
                
                [m_pDataProvider release];
            }

            Menu::View::MenuController& SettingsMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            SettingsMenuView& SettingsMenuViewModule::GetSettingsMenuView() const
            {
                return *m_pView;
            }*/
        }
    }
}
