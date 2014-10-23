// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "IPlaceJumpController.h"
#include "IPlaceJumpsModel.h"
#include "Logger.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        class PlaceJumpMenuOption : public Menu::IMenuOption
        {
        public:
            PlaceJumpMenuOption(PlaceJumpModel jumpModel,
                                IPlaceJumpController& jumpController,
                                ExampleApp::Menu::IMenuViewModel& menuViewModel)
            : m_jumpModel(jumpModel)
            , m_jumpController(jumpController)
            , m_menuViewModel(menuViewModel)
            {
            }
            
            void Select()
            {
                EXAMPLE_LOG("Jumping to %f,%f (%s)\n", m_jumpModel.GetLocation().GetLatitudeInDegrees(), m_jumpModel.GetLocation().GetLongitudeInDegrees(), m_jumpModel.GetName().c_str());
                
                m_jumpController.JumpTo(m_jumpModel);
                m_menuViewModel.Close();
            }
            
        private:
            
            PlaceJumpModel m_jumpModel;
            IPlaceJumpController& m_jumpController;
            ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
        };

    }
}
