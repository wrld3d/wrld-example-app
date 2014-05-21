/*
 * JavaHudCrossThreadCommunicationExampleFactory.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"

namespace Examples
{
    class JavaHudCrossThreadCommunicationExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        AndroidNativeState& m_nativeState;

    public:
        JavaHudCrossThreadCommunicationExampleFactory(
        		Eegeo::EegeoWorld& world,
        		AndroidNativeState& nativeState);

        IExample* CreateExample() const;
    };
}


#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_ */
