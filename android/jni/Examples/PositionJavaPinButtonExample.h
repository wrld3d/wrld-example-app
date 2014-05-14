/*
 * PositionJavaPinButton.h
 *
 *  Created on: Oct 31, 2013
 *      Author: kimbleoperations
 */

#ifndef POSITIONJAVAPINBUTTON_H_
#define POSITIONJAVAPINBUTTON_H_

#include <jni.h>
#include "EegeoWorld.h"
#include "IExample.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"


namespace Examples
{
    class PositionJavaPinButtonExample : public IExample
    {
    	AndroidNativeState& m_nativeState;
    	Eegeo::Rendering::RenderContext& m_renderContext;
		Eegeo::EegeoWorld& m_world;

    	int m_buttonID;
    	jclass m_hudPinControllerClass;
    	jobject m_hudPinController;
    	jmethodID m_updateLocationMethodId;

    public:
    	PositionJavaPinButtonExample(
    			Eegeo::EegeoWorld& world,
    			AndroidNativeState& pNativeState,
    			Eegeo::Rendering::RenderContext& renderContext);

        void Start() {}
        void Update(float dt) {}
        void Draw();
        void Suspend();

    private:
        void CreateButton();
        void Project (const Eegeo::Space::LatLongAltitude& location, Eegeo::v3& screenPosition);
    };
}

#endif /* POSITIONJAVAPINBUTTON_H_ */
