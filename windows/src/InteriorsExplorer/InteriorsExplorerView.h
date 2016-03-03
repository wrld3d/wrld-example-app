// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorsExplorerView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "ReflectionHelpers.h"
#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerView : public IInteriorsExplorerView, private Eegeo::NonCopyable
            {
            private:
                
                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Eegeo::Helpers::CallbackCollection1<int> m_selectedFloorCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                Eegeo::Helpers::CallbackCollection1<float> m_floorSelectionDraggedCallbacks;

                Helpers::ReflectionHelpers::Method<array<System::String^>^, int> mUpdateFloors;
                Helpers::ReflectionHelpers::Method<System::String^> mSetFloorName;
                Helpers::ReflectionHelpers::Method<int> mSetSelectedFloor;
                Helpers::ReflectionHelpers::Method<float> mSetOnScreenStateToIntermediateValue;
                Helpers::ReflectionHelpers::Method<void> mSetFullyOnScreen;
                Helpers::ReflectionHelpers::Method<void> mSetFullyOffScreen;
                Helpers::ReflectionHelpers::Method<bool> mSetTouchEnabled;
                Helpers::ReflectionHelpers::Method<bool> mSetFloorPanelEnabled;
                Helpers::ReflectionHelpers::Method<void> mDestroy;

            public:
                InteriorsExplorerView();

                ~InteriorsExplorerView();

                void UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex);

                void SetFloorName(const std::string& name);

                void SetFloorSelectionDrag(float dragParam);

                void SetSelectedFloorIndex(int index);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void SetTouchEnabled(bool enabled);

                void SetFloorPanelEnabled(bool enabled);

                void Dismiss();

                void SelectFloor(int floor);

                void OnDismissed();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

                void RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

                void InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);
                
                void RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback);


            };
        }
    }
}


//// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
//
//#pragma once
//
//#import <UIKit/UIKit.h>
//#include "InteriorsExplorerViewIncludes.h"
//#include <string>
//#include <vector>
//
//@class InteriorsExplorerView;
//
//@interface InteriorsExplorerView : UIView <UITableViewDelegate, UITableViewDataSource>
//{
//    ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop* m_pInterop;
//    
//    float m_width;
//    float m_height;
//    
//    float m_screenWidth;
//    float m_screenHeight;
//    float m_pixelScale;
//    
//    float m_inactiveFloorListXPosition;
//    float m_inactiveDetailPaneYPosition;
//    
//    float m_onScreenParam;
//    float m_stateChangeAnimationTimeSeconds;
//    
//    float m_detailsPanelHeight;
//    
//    BOOL m_touchEnabled;
//    
//    std::vector<std::string> m_tableViewFloorNames;
//}
//
//- (id) initWithParams:(float)width :(float)height :(float)pixelScale;
//
//- (ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop*) getInterop;
//
//- (BOOL)consumesTouch:(UITouch *)touch;
//
//- (void) show;
//
//- (void) hide;
//
//- (void) setFloorName:(const std::string*)name;
//
//- (void) setSelectedFloor:(int)floorIndex;
//
//- (void) updateFloors: (const std::vector<std::string>&) floorNumbers withCurrentFloor: (int) currentlySelectedFloor;
//
//- (void) setFullyOnScreen;
//
//- (void) setFullyOffScreen;
//
//- (void) setOnScreenStateToIntermediateValue:(float)openState;
//
//- (void) animateTo:(float)t;
//
//- (int) reverseIndex:(int)floorIndex;
//
//- (void) setTouchEnabled:(BOOL)enabled;
//
//- (void) setFloorPanelEnabled:(BOOL)enabled;
//
//@property(nonatomic, retain) UIView* pFloorPanel;
//@property(nonatomic, retain) UIImageView* pFloorPanelTop;
//@property(nonatomic, retain) UIImageView* pFloorPanelBottom;
//@property(nonatomic, retain) UITableView* pFloorList;
//
//@property(nonatomic, retain) UIView* pDetailsPanel;
//@property(nonatomic, retain) UIImageView* pDetailsPanelBackground;
//@property(nonatomic, retain) UIImageView* pDetailsPanelRight;
//
//@property(nonatomic, retain) UIButton* pDismissButton;
//@property(nonatomic, retain) UIImageView* pDismissButtonBackground;
//@property(nonatomic, retain) UILabel* pFloorNameLabel;
//
//@end