// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "BidirectionalBus.h"
#include "Menu.h"
#include "MyPinCreation.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"
#include <sstream>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerController
            {
            public:
                
                InteriorsExplorerController(IInteriorsExplorerView& view,
                                            InteriorsExplorerViewModel& viewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                            ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                            ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel,
                                            ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                            ScreenControl::View::IScreenControlViewModel& compassViewModel,
											ScreenControl::View::IScreenControlViewModel& watermarkModel);
                
                ~InteriorsExplorerController();
                
            private:
                
                void OnDismiss();
                void OnSelectFloor(int& selected);
                void OnFloorSelected(const InteriorsExplorerFloorSelectedMessage& message);
                void OnStateChanged(const InteriorsExplorerStateChangedMessage& message);
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state);
                
                IInteriorsExplorerView& m_view;
                InteriorsExplorerViewModel& m_viewModel;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerController> m_dismissedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, int> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerStateChangedMessage&> m_stateChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerFloorSelectedMessage&> m_floorSelectedCallback;
                Eegeo::Helpers::TCallback2<InteriorsExplorerController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                
                MyPinCreation::View::IMyPinCreationInitiationViewModel& m_initiationViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_secondaryMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_searchResultMenuViewModel;
                ScreenControl::View::IScreenControlViewModel& m_flattenViewModel;
                ScreenControl::View::IScreenControlViewModel& m_compassViewModel;
                ScreenControl::View::IScreenControlViewModel& m_watermarkViewModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
