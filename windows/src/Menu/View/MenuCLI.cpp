// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "MenuCLI.h"
#include "MenuViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    void MenuViewCLIMethods::ViewClicked(
        System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleViewClicked();
    }

    void MenuViewCLIMethods::ViewOpenCompleted(
        System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleViewOpenCompleted();
    }

    void MenuViewCLIMethods::ViewCloseCompleted(
        System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleViewCloseCompleted();
    }

    void MenuViewCLIMethods::ViewDragStarted(
        System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleDraggingViewStarted();
    }

    void MenuViewCLIMethods::ViewDragInProgress(
        System::IntPtr^ nativeObjectPtr,
        float normalisedDragState)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleDraggingViewInProgress(normalisedDragState);
    }

    void MenuViewCLIMethods::ViewDragCompleted(
        System::IntPtr^ nativeObjectPtr)
    {
        ASSERT_UI_THREAD

            ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleDraggingViewCompleted();
    }

    void MenuViewCLIMethods::SelectedItem(
        System::IntPtr^ nativeObjectPtr,
        int sectionIndex,
        int itemIndex)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        pView->HandleItemSelected(sectionIndex, itemIndex);
    }

    bool MenuViewCLIMethods::TryBeginDrag(
        System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::Menu::View::MenuViewImpl* pView = reinterpret_cast<ExampleApp::Menu::View::MenuViewImpl*>(nativeObjectPtr->ToPointer());
        return pView->CallBeginDrag();
    }
}