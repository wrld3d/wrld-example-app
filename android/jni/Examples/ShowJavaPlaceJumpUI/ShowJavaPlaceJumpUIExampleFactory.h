/*
 * ShowJavaPlaceJumpUIExampleFactory.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_
#define SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "ExampleCameraJumpController.h"
#include "AndroidNativeState.h"

namespace Examples
{
    class ShowJavaPlaceJumpUIExampleFactory : public IExampleFactory
    {
    	ExampleCameraJumpController& m_exampleCameraJumpController;
        AndroidNativeState& m_nativeState;

    public:
        ShowJavaPlaceJumpUIExampleFactory(
        		ExampleCameraJumpController& exampleCameraJumpController,
        		AndroidNativeState& nativeState);

        IExample* CreateExample() const;
    };
}


#endif /* SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_ */
