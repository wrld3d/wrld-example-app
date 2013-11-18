//
//  NavigationGraphExample.h
//  ExampleApp
//
//  Created by eeGeo on 02/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__NavigationGraphExample__
#define __ExampleApp__NavigationGraphExample__

#include "IExample.h"

#include "NavigationGraphRepository.h"
#include "NavigationGraphAddedCallback.h"
#include "NavigationGraphRemovalCallback.h"
#include "NavigationGraph.h"
#include "DebugRendering.h"
#include "RenderContext.h"


namespace Examples
{
    class NavigationGraphExample : public IExample
    {
    private:
        typedef std::map<const Eegeo::Resources::Roads::Navigation::NavigationGraph*, Eegeo::DebugRendering::DebugRenderable*> MapType;
        
        struct Added : public Eegeo::Resources::Roads::Navigation::INavigationGraphAddedCallback {
            NavigationGraphExample& example;
            Added(NavigationGraphExample& example):example(example){}
            void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph) { example.HandleAddedGraph(navGraph); }
        };
        
        struct Removed : public Eegeo::Resources::Roads::Navigation::INavigationGraphRemovalCallback {
            NavigationGraphExample& example;
            Removed(NavigationGraphExample& example):example(example){}
            void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph) { example.HandleRemovedGraph(navGraph); }
        };
        
        
        void HandleAddedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
        void HandleRemovedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& navigationGraphRepository;
        
        Added addedHandler;
        Removed removedHandler;
        MapType navGraphsToVisualisers;
        
    public:
        NavigationGraphExample(Eegeo::Rendering::RenderContext& renderContext,
                               Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& navigationGraphRepository);
        
        void Start();
        void Update(float dt) {}
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__NavigationGraphExample__) */
