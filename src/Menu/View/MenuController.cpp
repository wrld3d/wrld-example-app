// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuController.h"
#include "IMenuOption.h"
#include "IOpenableControlViewModel.h"
#include "MenuDragStateChangedMessage.h"
#include "MenuSectionExpandedChangedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            void MenuController::OnMenuSectionExpandeStateChanged(IMenuSectionViewModel& menuSectionViewModel, bool& expanded)
            {
                m_messageBus.Publish(MenuSectionExpandedChangedMessage(menuSectionViewModel.Name(), expanded));
            }
            
            void MenuController::OnOpenableStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& state)
            {
                if(m_dragInProgress)
                {
                    return;
                }

                if(m_viewModel.IsAddedToScreen())
                {
                    if (m_viewModel.IsFullyClosed())
                    {
                        m_view.SetFullyOnScreenClosed();
                    }
                    else if (m_viewModel.IsFullyOpen())
                    {
                        m_view.SetFullyOnScreenOpen();
                    }
                    else
                    {
                        m_view.SetOnScreenStateToIntermediateValue(state);
                    }
                }
                else
                {
                    m_view.SetFullyOffScreen();
                }
            }

            void MenuController::OnScreenControlStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel, float& state)
            {
                if (m_viewModel.IsFullyOnScreen())
                {
                    m_view.SetFullyOnScreenClosed();
                }
                else if (m_viewModel.IsFullyOffScreen())
                {
                    m_view.SetFullyOffScreen();
                }
                else
                {
                    m_view.SetOnScreenStateToIntermediateValue(state);
                }
            }

            bool MenuController::TryDrag()
            {
                return m_viewModel.TryAcquireReactorControl();
            }

            void MenuController::RefreshPresentation(bool forceRefresh)
            {
                const size_t numSections = m_viewModel.SectionsCount();
                TSections sections;
                sections.reserve(numSections);

                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    IMenuSectionViewModel& section = m_viewModel.GetMenuSection(static_cast<int>(groupIndex));
                    sections.push_back(&section);
                }

                if(!m_viewModel.IsFullyClosed() || forceRefresh)
                {
                    m_view.UpdateMenuSectionViews(sections, m_menuContentsChanged);
                    m_presentationDirty = false;
                    m_menuContentsChanged = false;
                }
            }

            void MenuController::UpdateUiThread(float dt)
            {
                if(m_presentationDirty)
                {
                    RefreshPresentation(false);
                }

                if(m_dragInProgress)
                {
                    return;
                }

                const bool isAnimating = m_view.IsAnimating();

                if(isAnimating)
                {
                    m_view.UpdateAnimation(dt);

                    if(m_viewModel.HasReactorControl())
                    {
                        const float normalisedAnimationProgress = m_view.GetAnimationProgress();
                        m_viewModel.UpdateOpenState(normalisedAnimationProgress);
                    }
                }
                
                if(m_view.IsTableAnimating())
                {
                    m_view.UpdateTableAnimation(dt);
                }
                else
                {
                    m_view.SetTableCanInteract(m_viewModel.IsFullyOpen());
                }
            }

            void MenuController::OnViewClicked()
            {
                Eegeo_ASSERT(!m_dragInProgress, "Cannot click on view while dragging it");

                if(!m_viewModel.TryAcquireReactorControl())
                {
                    return;
                }

                if(m_viewModel.IsFullyClosed())
                {
                    m_view.SetFullyOnScreenOpen();
                }
                else if(m_viewModel.IsFullyOpen())
                {
                    m_view.SetFullyOnScreenClosed();
                }
                else
                {
                    m_viewModel.ReleaseReactorControl();
                }
            }

            void MenuController::OnViewOpened()
            {
                Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

                if (m_forceClose)
                {
                    m_viewModel.Close();
                    return;
                }

                if(!m_viewModel.IsFullyOpen())
                {
                    m_viewModel.Open();
                }

                if(m_viewModel.HasReactorControl())
                {
                    m_viewModel.ReleaseReactorControl();
                }
            }

            void MenuController::OnViewOpenStarted()
            {
                if(!m_viewModel.IsFullyOpen())
                {
                    m_viewModel.Open();
                }
            }

            void MenuController::OnViewClosed()
            {
                Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

                m_forceClose = false;

                if(!m_viewModel.IsFullyClosed())
                {
                    m_viewModel.Close();
                }

                if(m_viewModel.HasReactorControl())
                {
                    m_viewModel.ReleaseReactorControl();
                }
            }

            Eegeo::Helpers::TIdentity MenuController::Identity() const
            {
                return static_cast<OpenableControl::View::IOpenableControlViewModel&>(m_viewModel).GetIdentity();
            }

            void MenuController::OnDragStarted()
            {
                Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

                {
                    const bool acquiredReactorControl = m_viewModel.TryAcquireReactorControl();
                    Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
                }

                m_dragInProgress = true;
                m_messageBus.Publish(MenuDragStateChangedMessage(m_dragInProgress));
            }

            void MenuController::OnDrag(float& value)
            {
                Eegeo_ASSERT(m_dragInProgress);

                {
                    const bool acquiredReactorControl = m_viewModel.TryAcquireReactorControl();
                    Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
                }

                m_viewModel.UpdateOpenState(value);
            }

            void MenuController::OnDragCompleted()
            {
                Eegeo_ASSERT(m_dragInProgress);

                {
                    const bool acquiredReactorControl = m_viewModel.TryAcquireReactorControl();
                    Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
                }

                if(!m_viewModel.IsAddedToScreen())
                {
                    m_viewModel.Close();
                    m_view.SetFullyOffScreen();
                }
                m_dragInProgress = false;
                m_messageBus.Publish(MenuDragStateChangedMessage(m_dragInProgress));
            }

            void MenuController::OnItemAdded(MenuItemModel& item)
            {
                m_presentationDirty = true;
                m_menuContentsChanged = true;
            }

            void MenuController::OnItemRemoved(MenuItemModel& item)
            {
                m_presentationDirty = true;
                m_menuContentsChanged = true;
            }

            void MenuController::OnItemSelected(int& sectionIndex, int& itemIndex)
            {
                Eegeo_ASSERT(!m_dragInProgress, "Cannot select item on menu while dragging it");

                IMenuSectionViewModel& section = m_viewModel.GetMenuSection(sectionIndex);
                if (section.IsExpandable() && itemIndex == 0)
                {
                    if(section.IsExpanded())
                    {
                        section.Contract();
                    }
                    else
                    {
                        section.Expand();
                        for(int i = 0; i < m_viewModel.SectionsCount(); ++i)
                        {
                            if(i != sectionIndex)
                            {
                                m_viewModel.GetMenuSection(i).Contract();
                            }
                        }
                    }
                    m_presentationDirty = true;
                    return;
                }
                else
                {
                    const int index = section.IsExpandable() ? itemIndex - 1 : itemIndex;
                    section.GetItemAtIndex(index).MenuOption().Select();
                }
            }

            void MenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                const bool appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AppMode::AttractMode;
                if (!appModeAllowsOpen)
                {
                    m_viewModel.RemoveFromScreen();
                }
                else
                {
                    if (!m_viewModel.IsFullyOnScreen())
                    {
                        m_viewModel.AddToScreen();
                    }
                }

                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode)
                {
                    // Collapse all sections
                    for (size_t i = 0; i < m_viewModel.SectionsCount(); ++i)
                    {
                        m_viewModel.GetMenuSection(static_cast<int>(i)).Contract();
                    }

                    RefreshPresentation(true);
                    
                }
            }

            void MenuController::OnInteriorStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message) {
                if (!m_viewModel.IsFullyClosed())
                {
                    m_forceClose = true;
                    m_viewModel.Close();
                }
            }

            MenuController::MenuController(
                IMenuModel& model,
                IMenuViewModel& viewModel,
                IMenuView& view,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : m_model(model)
                , m_viewModel(viewModel)
                , m_view(view)
                , m_onClickedCallback(this, &MenuController::OnViewClicked)
                , m_onViewOpenedCallback(this, &MenuController::OnViewOpened)
                , m_onViewOpenStartedCallback(this, &MenuController::OnViewOpenStarted)
                , m_onViewClosedCallback(this, &MenuController::OnViewClosed)
                , m_onDragStartedCallback(this, &MenuController::OnDragStarted)
                , m_onDragCallback(this, &MenuController::OnDrag)
                , m_onDragCompletedCallback(this, &MenuController::OnDragCompleted)
                , m_onItemSelectedCallback(this, &MenuController::OnItemSelected)
                , m_onItemAddedCallback(this, &MenuController::OnItemAdded)
                , m_onItemRemovedCallback(this, &MenuController::OnItemRemoved)
                , m_onScreenStateChanged(this, &MenuController::OnScreenControlStateChanged)
                , m_onOpenableStateChanged(this, &MenuController::OnOpenableStateChanged)
                , m_onMenuSectionExpandedStateChanged(this, &MenuController::OnMenuSectionExpandeStateChanged)
                , m_onAppModeChanged(this, &MenuController::OnAppModeChanged)
                , m_onInteriorStateChangedCallback(this, & MenuController::OnInteriorStateChanged)
                , m_tryDragFunc(this, &MenuController::TryDrag)
                , m_messageBus(messageBus)
                , m_dragInProgress(false)
                , m_presentationDirty(false)
                , m_menuContentsChanged(true)
                , m_forceClose(false)
            {
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenableStateChanged);
                m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChanged);
                m_view.InsertOnDrag(m_onDragCallback);
                m_view.InsertOnDragCompleted(m_onDragCompletedCallback);
                m_view.InsertOnDragStarted(m_onDragStartedCallback);
                m_view.InsertOnItemSelected(m_onItemSelectedCallback);
                m_view.InsertOnViewClicked(m_onClickedCallback);
                m_view.InsertOnViewClosed(m_onViewClosedCallback);
                m_view.InsertOnViewOpenStarted(m_onViewOpenStartedCallback);
                m_view.InsertOnViewOpened(m_onViewOpenedCallback);
                m_view.SetTryDragFunc(m_tryDragFunc);

                m_messageBus.SubscribeUi(m_onAppModeChanged);
                m_messageBus.SubscribeUi(m_onInteriorStateChangedCallback);

                if(m_viewModel.IsFullyOnScreen())
                {
                    float value = m_viewModel.OpenState();
                    OnOpenableStateChanged(m_viewModel, value);
                }

                m_presentationDirty = true;
                
                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    IMenuSectionViewModel& section(m_viewModel.GetMenuSection(static_cast<int>(i)));
                    section.InsertExpandedChangedCallback(m_onMenuSectionExpandedStateChanged);
                    IMenuModel& menuModel = section.GetModel();
                    menuModel.InsertItemAddedCallback(m_onItemAddedCallback);
                    menuModel.InsertItemRemovedCallback(m_onItemRemovedCallback);
                }
            }

            MenuController::~MenuController()
            {
                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    IMenuSectionViewModel& section(m_viewModel.GetMenuSection(static_cast<int>(i)));
                    section.RemoveExpandedChangedCallback(m_onMenuSectionExpandedStateChanged);
                    IMenuModel& model = section.GetModel();
                    model.RemoveItemAddedCallback(m_onItemAddedCallback);
                    model.RemoveItemRemovedCallback(m_onItemRemovedCallback);
                }

                m_messageBus.UnsubscribeUi(m_onAppModeChanged);
                m_messageBus.UnsubscribeUi(m_onInteriorStateChangedCallback);
                
                m_view.ClearTryDragFunc();
                m_view.RemoveOnViewOpened(m_onViewOpenedCallback);
                m_view.RemoveOnViewOpenStarted(m_onViewOpenStartedCallback);
                m_view.RemoveOnViewClosed(m_onViewClosedCallback);
                m_view.RemoveOnViewClicked(m_onClickedCallback);
                m_view.RemoveOnItemSelected(m_onItemSelectedCallback);
                m_view.RemoveOnDragStarted(m_onDragStartedCallback);
                m_view.RemoveOnDragCompleted(m_onDragCompletedCallback);
                m_view.RemoveOnDrag(m_onDragCallback);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChanged);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenableStateChanged);
            }
        }
    }
}
