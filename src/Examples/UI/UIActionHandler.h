//
//  IUIActionHandler.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__UIActionHandler__
#define __ExampleApp__UIActionHandler__

#include "IUIActionHandler.h"
#include "Types.h"

namespace Examples
{
    template <class T> class UIActionHandler : public IUIActionHandler, private Eegeo::NonCopyable
    {
    private:
        void (T::*m_callback)();
        T* m_context;
    public:
        UIActionHandler(T* context, void (T::*callback)())
        : m_context(context)
        , m_callback(callback)
        {
        }
        
        virtual void operator()()
        {
            (*m_context.*m_callback)();
        }
    };
}


#endif /* defined(__ExampleApp__UIActionHandler__) */
