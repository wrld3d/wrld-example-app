// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuModule.h"

#include "IReactionControllerModel.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuSectionViewModel.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionsMenuModule::DirectionsMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                               ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                             ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService)
            : m_pMenuModel(NULL)
            , m_pMenuViewModel(NULL)
            , m_pSearchSectionViewModel(NULL)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                
                m_pMenuViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                                                                        identityProvider.GetNextIdentity(),
                                                                        reactionControllerModel);
            }
            
            DirectionsMenuModule::~DirectionsMenuModule()
            {
                Eegeo_DELETE m_pMenuViewModel;
                Eegeo_DELETE m_pMenuModel;
            }
            
            void DirectionsMenuModule::SetDirectionsSection(const std::string& name,
                                                    Menu::View::IMenuModel& menuModel)
            {
                m_pSearchSectionViewModel = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, false);
            }

            
            Menu::View::IMenuModel& DirectionsMenuModule::GetDirectionsMenuModel() const
            {
                return *m_pMenuModel;
            }
            
            Menu::View::IMenuViewModel& DirectionsMenuModule::GetDirectionsMenuViewModel() const
            {
                return *m_pMenuViewModel;
            }
            Menu::View::IMenuSectionViewModel& DirectionsMenuModule::GetDirectionsSectionViewModel() const
            {
                Eegeo_ASSERT(m_pSearchSectionViewModel != NULL, "Search section view model not set, please call SetSearchSection before calling this function");
                
                return *m_pSearchSectionViewModel;
            }
        }
    }
}