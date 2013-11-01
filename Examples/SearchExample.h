//
//  SearchExample.h
//  ExampleApp
//
//  Created by Scott on 18/06/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__SearchExample__
#define __ExampleApp__SearchExample__

#include "IExample.h"
#include "SearchService.h"
#include "IPoiSearchCallback.h"
#include "Location.h"

namespace Examples
{
    //To use the search example, you should #define USING_SEARCH_EXAMPLE in ViewController.mm and input your credentials
    class SearchExample : public IExample, public Eegeo::Search::Service::IPoiSearchCallback
    {
    private:
        Eegeo::Search::Service::SearchService& searchService;
        Eegeo::Location::IInterestPointProvider& interestPointProvider;
        
    public:
        SearchExample(Eegeo::Search::Service::SearchService& searchService,
                      Eegeo::Location::IInterestPointProvider& interestPointProvider);
        
        void Start();
        void Update() {}
        void Draw() {}
        void Suspend() {}
        
        void HandlePoiSearchResults(const Eegeo::Search::Service::PoiSearchResult& result);
    };
}

#endif /* defined(__ExampleApp__SearchExample__) */
