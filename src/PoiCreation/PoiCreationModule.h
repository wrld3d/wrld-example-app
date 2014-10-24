// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreation.h"
#include "IPoiCreationModule.h"
#include "Modules.h"
#include "VectorMathDecl.h"
#include "Camera.h"
#include "Rendering.h"
#include "Terrain.h"
#include "IIdentity.h"
#include "SearchResultMenu.h"
#include "Menu.h"
#include "Search.h"
#include "IdTypes.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationModule : public IPoiCreationModule
        {
        public:
            PoiCreationModule(MyPins::IMyPinsService& myPinsService,
                              Eegeo::Helpers::IIdentityProvider& identityProvider,
                              ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                              ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                              ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                              ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel);
            
            ~PoiCreationModule();
            
            IPoiCreationModel& GetPoiCreationModel() const;
            IPoiCreationButtonViewModel& GetPoiCreationButtonViewModel() const;
            IPoiCreationConfirmationViewModel& GetPoiCreationConfirmationViewModel() const;
            IPoiCreationCompositeViewModel& GetPoiCreationCompositeViewModel() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetButtonScreenControlViewModel() const;
            ScreenControlViewModel::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const;
            
        private:
    
            PoiCreationModel* m_pPoiCreationModel;
            PoiCreationButtonViewModel* m_pPoiCreationButtonViewModel;
            PoiCreationConfirmationViewModel* m_pPoiCreationConfirmationViewModel;
            PoiCreationCompositeViewModel* m_pPoiCreationCompositeViewModel;
        };
    }
}