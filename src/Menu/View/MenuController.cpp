// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuController.h"
#include "IOpenableControlViewModel.h"
#include "MenuDragStateChangedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
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
                if(m_viewModel.TryAcquireReactorControl())
                {
                    return true;
                }
                return false;
            }

            void MenuController::RefreshPresentation()
            {
                const int numSections = m_viewModel.SectionsCount();
                TSections sections;
                sections.reserve(numSections);

                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    IMenuSectionViewModel& section = m_viewModel.GetMenuSection(groupIndex);
                    sections.push_back(&section);
                }

                if(!m_viewModel.IsFullyClosed())
                {
                    m_view.UpdateMenuSectionViews(sections);
                    m_presentationDirty = false;
                }
            }

            void MenuController::UpdateUiThread(float dt)
            {
                if(m_presentationDirty)
                {
                    RefreshPresentation();
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

                m_view.SetCanInteract(m_viewModel.IsFullyOpen());
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

                if(!m_viewModel.IsFullyOpen())
                {
                    m_viewModel.Open();
                }

                if(m_viewModel.HasReactorControl())
                {
                    m_viewModel.ReleaseReactorControl();
                }
            }

            void MenuController::OnViewClosed()
            {
                Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

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
            }

            void MenuController::OnItemRemoved(MenuItemModel& item)
            {
                m_presentationDirty = true;
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
                    }
                    m_presentationDirty = true;
                    return;
                }
                else
                {
                    int index = section.IsExpandable() ? itemIndex - 1 : itemIndex;
                    MenuItemModel item = section.GetItemAtIndex(index);
                    item.Select();
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
                , m_onViewClosedCallback(this, &MenuController::OnViewClosed)
                , m_onDragStartedCallback(this, &MenuController::OnDragStarted)
                , m_onDragCallback(this, &MenuController::OnDrag)
                , m_onDragCompletedCallback(this, &MenuController::OnDragCompleted)
                , m_onItemSelectedCallback(this, &MenuController::OnItemSelected)
                , m_onItemAddedCallback(this, &MenuController::OnItemAdded)
                , m_onItemRemovedCallback(this, &MenuController::OnItemRemoved)
                , m_onScreenStateChanged(this, &MenuController::OnScreenControlStateChanged)
                , m_onOpenableStateChanged(this, &MenuController::OnOpenableStateChanged)
                , m_tryDragFunc(this, &MenuController::TryDrag)
                , m_messageBus(messageBus)
                , m_dragInProgress(false)
                , m_presentationDirty(false)
            {
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenableStateChanged);
                m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChanged);
                m_view.InsertOnDrag(m_onDragCallback);
                m_view.InsertOnDragCompleted(m_onDragCompletedCallback);
                m_view.InsertOnDragStarted(m_onDragStartedCallback);
                m_view.InsertOnItemSelected(m_onItemSelectedCallback);
                m_view.InsertOnViewClicked(m_onClickedCallback);
                m_view.InsertOnViewClosed(m_onViewClosedCallback);
                m_view.InsertOnViewOpened(m_onViewOpenedCallback);
                m_view.SetTryDragFunc(m_tryDragFunc);

                if(m_viewModel.IsFullyOnScreen())
                {
                    float value = m_viewModel.OpenState();
                    OnOpenableStateChanged(m_viewModel, value);
                }

                m_presentationDirty = true;
                
                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    IMenuSectionViewModel& section(m_viewModel.GetMenuSection(i));
                    IMenuModel& model = section.GetModel();
                    model.InsertItemAddedCallback(m_onItemAddedCallback);
                    model.InsertItemRemovedCallback(m_onItemRemovedCallback);
                }
            }

            MenuController::~MenuController()
            {
                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    IMenuSectionViewModel& section(m_viewModel.GetMenuSection(i));
                    IMenuModel& model = section.GetModel();
                    model.RemoveItemAddedCallback(m_onItemAddedCallback);
                    model.RemoveItemRemovedCallback(m_onItemRemovedCallback);
                }
                
                m_view.ClearTryDragFunc();
                m_view.RemoveOnViewOpened(m_onViewOpenedCallback);
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
