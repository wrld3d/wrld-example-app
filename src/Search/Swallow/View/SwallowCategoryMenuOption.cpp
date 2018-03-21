// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowCategoryMenuOption.h"
#include "IMenuViewModel.h"
#include "TagSearchSelectedMessage.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace View
            {
                SwallowCategoryMenuOption::SwallowCategoryMenuOption(std::string category,
                                                                     bool interiorSearchAllowed,
                                                                     bool closeMenuOnSelect,
                                                                     Menu::View::IMenuViewModel& menuViewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_category(category)
                , m_interiorSearchAllowed(interiorSearchAllowed)
                , m_hasRadiusOverride(false)
                , m_radiusOverride(0.f)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_inInteriorMode(false)
                , m_closeMenuOnSelect(closeMenuOnSelect)
                , m_appModeChangedHandler(this, &SwallowCategoryMenuOption::OnAppModeChangedMessage)
                {
                    m_messageBus.SubscribeUi(m_appModeChangedHandler);
                }
                
                SwallowCategoryMenuOption::SwallowCategoryMenuOption(std::string category,
                                                                     bool interiorSearchAllowed,
                                                                     bool closeMenuOnSelect,
                                                                     Menu::View::IMenuViewModel& menuViewModel,
                                                                     float radius,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_category(category)
                , m_interiorSearchAllowed(interiorSearchAllowed)
                , m_hasRadiusOverride(true)
                , m_radiusOverride(radius)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_inInteriorMode(false)
                , m_closeMenuOnSelect(closeMenuOnSelect)
                , m_appModeChangedHandler(this, &SwallowCategoryMenuOption::OnAppModeChangedMessage)
                {
                    m_messageBus.SubscribeUi(m_appModeChangedHandler);
                }
                
                SwallowCategoryMenuOption::~SwallowCategoryMenuOption()
                {
                    m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                }
                
                void SwallowCategoryMenuOption::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
                {
                    m_inInteriorMode = message.GetAppMode() == AppModes::SdkModel::InteriorMode;
                }
                
                void SwallowCategoryMenuOption::Select()
                {
                    if (m_closeMenuOnSelect)
                    {
                        m_menuViewModel.Close();
                    }

                    /*
                     * Not anymore
                     *
                    bool shouldZoomToBuildingsView = true;

                    if (m_hasRadiusOverride)
                    {
                        m_messageBus.Publish(TagSearch::TagSearchSelectedMessage(m_category, m_interiorSearchAllowed, shouldZoomToBuildingsView, m_radiusOverride));
                    }
                    else
                    {
                        m_messageBus.Publish(TagSearch::TagSearchSelectedMessage(m_category, m_interiorSearchAllowed, shouldZoomToBuildingsView));
                    }
                    */
                }
            }
        }
    }
}
