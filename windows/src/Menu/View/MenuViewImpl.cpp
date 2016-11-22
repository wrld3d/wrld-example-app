// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {

            MenuViewImpl::MenuViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState,
                               const std::string& viewClassName)
                : m_nativeState(nativeState)
                , m_pTryDragFunc(NULL)
            {
                System::String^ className = gcnew System::String(viewClassName.c_str());
                m_uiViewClass = GetTypeFromEntryAssembly(className);
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

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
            }

            MenuViewImpl::~MenuViewImpl()
            {
                Destroy();
            }

            void MenuViewImpl::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
                Eegeo_ASSERT(m_pTryDragFunc == NULL, "TryDragFunc already set");
                m_pTryDragFunc = &function;
            }

            void MenuViewImpl::ClearTryDragFunc()
            {
                m_pTryDragFunc = NULL;
            }

            float MenuViewImpl::GetAnimationProgress() const
            {
                return (float)NormalisedAnimationProgress.Call<System::Single^>();
            }

            bool MenuViewImpl::IsAnimating() const
            {
                return (bool)IsAnimatingCSharp.Call<System::Boolean^>();
            }

            void MenuViewImpl::UpdateAnimation(float dt)
            {
                UpdateAnimationCSharp(dt);
            }

            void MenuViewImpl::UpdateMenuSectionViews(TSections& sections, bool contentsChanged)
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
                    groupIsExpandableArray[static_cast<int>(groupIndex)] = static_cast<System::Boolean>(section.IsExpandable());
                }

                PopulateData(System::IntPtr(this),
                    groupNamesArray,
                    groupSizesArray,
                    groupIsExpandableArray,
                    childNamesArray);
            }

            void MenuViewImpl::SetFullyOnScreenOpen()
            {
                AnimateToOpenOnScreen();
            }

            void MenuViewImpl::SetFullyOnScreenClosed()
            {
                AnimateToClosedOnScreen();
            }

            void MenuViewImpl::SetOnScreenStateToIntermediateValue(float value)
            {
                AnimateToIntermediateOnScreenState(value);
            }

            void MenuViewImpl::SetFullyOnScreen()
            {
                AnimateToClosedOnScreen();
            }

            void MenuViewImpl::SetFullyOffScreen()
            {
                AnimateOffScreen();
            }

            void MenuViewImpl::InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClickedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClickedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragStartedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragStartedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_onDragCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                m_onDragCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragCompletedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                m_onDragCompletedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void MenuViewImpl::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void MenuViewImpl::HandleViewClicked()
            {
                m_onViewClickedCallbacks.ExecuteCallbacks();
            }

            void MenuViewImpl::HandleViewOpenCompleted()
            {
                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void MenuViewImpl::HandleViewCloseCompleted()
            {
                m_onViewClosedCallbacks.ExecuteCallbacks();
            }

            void MenuViewImpl::HandleDraggingViewStarted()
            {
                m_onDragStartedCallbacks.ExecuteCallbacks();
            }

            void MenuViewImpl::HandleDraggingViewInProgress(float progress)
            {
                m_onDragCallbacks.ExecuteCallbacks(progress);
            }

            void MenuViewImpl::HandleDraggingViewCompleted()
            {
                m_onDragCompletedCallbacks.ExecuteCallbacks();
            }

            void MenuViewImpl::HandleItemSelected(int sectionIndex, int itemIndex)
            {
                m_onItemSelectedCallbacks.ExecuteCallbacks(sectionIndex, itemIndex);
            }

            bool MenuViewImpl::CallBeginDrag()
            {
                Eegeo_ASSERT(m_pTryDragFunc != NULL, "No drag function registered");
                return (*m_pTryDragFunc)();
            }

            void MenuViewImpl::SetCanInteract(bool canInteract)
            {
                // This is already handled in the Java-side View on Android
            }
        }
    }
}
