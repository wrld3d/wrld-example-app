// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"
#include "IMenuSectionViewModel.h"
#include "IMenuModel.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {

            MenuView::MenuView(WindowsNativeState& nativeState,
                               const std::string& viewClassName,
                               bool isInKioskMode)
                : m_nativeState(nativeState)
                , m_pTryDragFunc(NULL)
            {
                System::String^ className = gcnew System::String(viewClassName.c_str());
                m_uiViewClass = GetTypeFromEntryAssembly(className);
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid, System::Boolean::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this), gcnew System::Boolean(isInKioskMode)));

                Destroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                NormalisedAnimationProgress.SetupMethod(m_uiViewClass, m_uiView, "NormalisedAnimationProgress");
                IsAnimatingCSharp.SetupMethod(m_uiViewClass, m_uiView, "IsAnimating");
                UpdateAnimationCSharp.SetupMethod(m_uiViewClass, m_uiView, "UpdateAnimation");
                PopulateData.SetupMethod(m_uiViewClass, m_uiView, "PopulateData");
                AnimateToOpenOnScreen.SetupMethod(m_uiViewClass, m_uiView, "AnimateToOpenOnScreen");
                AnimateToClosedOnScreen.SetupMethod(m_uiViewClass, m_uiView, "AnimateToClosedOnScreen");
                AnimateToOpenOnScreen.SetupMethod(m_uiViewClass, m_uiView, "AnimateToOpenOnScreen");
                AnimateOffScreen.SetupMethod(m_uiViewClass, m_uiView, "AnimateOffScreen");
                AnimateToIntermediateOnScreenState.SetupMethod(m_uiViewClass, m_uiView, "AnimateToIntermediateOnScreenState");
                mToggleSection.SetupMethod(m_uiViewClass, m_uiView, "ToggleSection");
            }

            MenuView::~MenuView()
            {
                Destroy();
            }

            void MenuView::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
                Eegeo_ASSERT(m_pTryDragFunc == NULL, "TryDragFunc already set");
                m_pTryDragFunc = &function;
            }

            void MenuView::ClearTryDragFunc()
            {
                m_pTryDragFunc = NULL;
            }

            float MenuView::GetAnimationProgress() const
            {
                return (float)NormalisedAnimationProgress.Call<System::Single^>();
            }

            bool MenuView::IsAnimating() const
            {
                return (bool)IsAnimatingCSharp.Call<System::Boolean^>();
            }

            void MenuView::UpdateAnimation(float dt)
            {
                UpdateAnimationCSharp(dt);
            }

            void MenuView::UpdateMenuSectionViews(TSections& sections, bool contentsChanged)
            {
                const size_t numSections = sections.size();
                size_t numItems = 0;
                for (size_t i = 0; i < numSections; ++i)
                {
                    const IMenuSectionViewModel& section = *(sections.at(i));
                    numItems += section.Size();
                }

                array<System::String^>^ groupNamesArray = gcnew array<System::String^>(static_cast<int>(numSections));
                array<System::Int32>^ groupSizesArray = gcnew array<System::Int32>(static_cast<int>(numSections));
                array<System::Boolean>^ groupIsExpandableArray = gcnew array<System::Boolean>(static_cast<int>(numSections));
                array<System::String^>^ childNamesArray = gcnew array<System::String^>(static_cast<int>(numItems));

                size_t currentChildIndex = 0;
                for (size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    const IMenuSectionViewModel& section = *(sections.at(groupIndex));
                    for (size_t childIndex = 0; childIndex < section.Size(); childIndex++)
                    {
                        int itemIndex = static_cast<int>(section.IsExpandable() ? childIndex - 1 : childIndex);
                        std::string jsonData = section.IsExpandable() && childIndex == 0
                            ? section.SerializeJson()
                            : section.GetItemAtIndex(itemIndex).SerializeJson();
                        childNamesArray[static_cast<int>(currentChildIndex)] = ConvertUTF8ToManagedString(jsonData);
                        currentChildIndex++;
                    }
                    
                    groupNamesArray[static_cast<int>(groupIndex)] = ConvertUTF8ToManagedString(section.Name().c_str());
                    groupSizesArray[static_cast<int>(groupIndex)] = static_cast<System::Int32>(section.Size());
                    groupIsExpandableArray[static_cast<int>(groupIndex)] = static_cast<System::Boolean>(section.IsExpandable()) && section.GetModel().GetItemCount() > 0;
                }

                PopulateData(System::IntPtr(this),
                    groupNamesArray,
                    groupSizesArray,
                    groupIsExpandableArray,
                    childNamesArray);
            }

            void MenuView::SetFullyOnScreenOpen()
            {
                AnimateToOpenOnScreen();
            }

            void MenuView::SetFullyOnScreenClosed()
            {
                AnimateToClosedOnScreen();
            }

            void MenuView::SetOnScreenStateToIntermediateValue(float value)
            {
                AnimateToIntermediateOnScreenState(value);
            }

            void MenuView::SetFullyOnScreen()
            {
                AnimateToClosedOnScreen();
            }

            void MenuView::SetFullyOffScreen()
            {
                AnimateOffScreen();
            }

            void MenuView::InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClickedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClickedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenStartedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenStartedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragStartedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragStartedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_onDragCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_onDragCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragCompletedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragCompletedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void MenuView::HandleViewClicked()
            {
                m_onViewClickedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewOpenCompleted()
            {
                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewOpenStarted()
            {
                m_onViewOpenStartedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewCloseCompleted()
            {
                m_onViewClosedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleDraggingViewStarted()
            {
                m_onDragStartedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleDraggingViewInProgress(float progress)
            {
                m_onDragCallbacks.ExecuteCallbacks(progress);
            }

            void MenuView::HandleDraggingViewCompleted()
            {
                m_onDragCompletedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleItemSelected(int sectionIndex, int itemIndex)
            {
                m_onItemSelectedCallbacks.ExecuteCallbacks(sectionIndex, itemIndex);
            }

            bool MenuView::CallBeginDrag()
            {
                Eegeo_ASSERT(m_pTryDragFunc != NULL, "No drag function registered");
                return (*m_pTryDragFunc)();
            }

            void MenuView::SetCanInteract(bool canInteract)
            {
                // This is already handled in the Java-side View on Android
            }

            void MenuView::ToggleSection(int sectionIndex)
            {
                mToggleSection(sectionIndex);
            }
        }
    }
}
