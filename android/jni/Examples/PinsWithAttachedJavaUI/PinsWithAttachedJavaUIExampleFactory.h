/*
 * PinsWithAttachedJavaUIExampleFactory.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef PINSWITHATTACHEDUIEXAMPLEFACTORY_H_
#define PINSWITHATTACHEDUIEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"

namespace Examples
{
    class PinsWithAttachedJavaUIExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        AndroidNativeState& m_nativeState;

    public:
        PinsWithAttachedJavaUIExampleFactory(
        		Eegeo::EegeoWorld& world,
        		AndroidNativeState& nativeState);

        IExample* CreateExample() const;
    };
}


#endif /* PINSWITHATTACHEDUIEXAMPLEFACTORY_H_ */
