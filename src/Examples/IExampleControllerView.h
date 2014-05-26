//
//  IExampleControllerView.h
//  ExampleApp
//
//  Created by Scott on 23/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IExampleControllerView_h
#define ExampleApp_IExampleControllerView_h

#include "IUIActionHandler.h"
#include <string>

namespace Examples
{
    class IExampleControllerView
    {
    public:
        virtual ~IExampleControllerView() {}
        
        virtual void AddSelectPreviousExampleHandler(IUIActionHandler& handler)=0;
        
        virtual void RemoveSelectPreviousExampleHandler(IUIActionHandler& handler)=0;
        
        virtual void AddSelectNextExampleHandler(IUIActionHandler& handler)=0;
        
        virtual void SetCurrentExampleName(const std::string& name)=0;
        
        virtual void RemoveSelectNextExampleHandler(IUIActionHandler& handler)=0;
        
        virtual void AddExampleSelectedHandler(IUIActionHandler& handler)=0;
        
        virtual void RemoveExampleSelectedHandler(IUIActionHandler& handler)=0;
        
        virtual std::string GetSelectedExample()=0;
    };
}

#endif
