// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerCLI.h"
#include "InteriorsExplorerView.h"

namespace ExampleApp
{
    void InteriorsExplorerCLIMethods::Dismiss(System::IntPtr nativeObjectPtr)
    {
        InteriorsExplorer::View::InteriorsExplorerView* view = reinterpret_cast<InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr.ToPointer());
        view->Dismiss();
    }

    void InteriorsExplorerCLIMethods::SelectFloor(System::IntPtr nativeObjectPtr, int index)
    {
        InteriorsExplorer::View::InteriorsExplorerView* view = reinterpret_cast<InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr.ToPointer());
        view->SelectFloor(index);
    }

    void InteriorsExplorerCLIMethods::SetFloorSelectionDrag(System::IntPtr nativeObjectPtr, System::Double dragParam)
    {
        InteriorsExplorer::View::InteriorsExplorerView* view = reinterpret_cast<InteriorsExplorer::View::InteriorsExplorerView*>(nativeObjectPtr.ToPointer());
        view->SetFloorSelectionDrag(static_cast<float>(dragParam));
    }
}