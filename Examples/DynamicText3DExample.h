//
//  DynamicText3DExample.h
//  ExampleApp
//
//  Created by Scott on 25/02/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__DynamicText3DExample__
#define __ExampleApp__DynamicText3DExample__

#include <vector>
#include <string>
#include "IExample.h"

#include "PlaceNameView.h"
#include "ICameraProvider.h"
#include "EnvironmentFlatteningService.h"
#include "PlaceNameView.h"
#include "PlaceNameViewBuilder.h"
#include "GlState.h"
#include "EegeoWorld.h"

namespace Examples
{
    class DynamicText3DExample : public IExample
    {
        Eegeo::Rendering::GLState& m_glState;
        Eegeo::Camera::ICameraProvider& m_cameraProvider;
        Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
        Eegeo::Resources::PlaceNames::PlaceNameViewBuilder& m_placeNameViewBuilder;
        Eegeo::EegeoWorld& m_world;
        
        bool m_initialised;
        std::vector<Eegeo::Resources::PlaceNames::PlaceNameView*> m_views;
        
    public:
        DynamicText3DExample(Eegeo::Rendering::GLState& glState,
                             Eegeo::Camera::ICameraProvider& cameraProvider,
                             Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                             Eegeo::Resources::PlaceNames::PlaceNameViewBuilder& placeNameViewBuilder,
                             Eegeo::EegeoWorld& world);
        
        void Start() { }
        void Update(float dt);
        void Draw();
        void Suspend();
        
    private:
        void CreateDynamic3DText(const std::string& str,
                                 float fontPointSize,
                                 double latitudeDegrees,
                                 double longitudeDegrees,
                                 const Eegeo::v3& colour,
                                 float alpha);
    };
}

#endif /* defined(__ExampleApp__DynamicText3DExample__) */
