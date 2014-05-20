/*
 * PositionJavaPinButton.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: kimbleoperations
 */

#include <jni.h>
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "PositionJavaPinButtonExample.h"

namespace Examples
{
	//this is the native companion type to com.eegeo.examples.HudPinController.java
	//
	PositionJavaPinButtonExample::PositionJavaPinButtonExample(
			Eegeo::EegeoWorld& world,
			AndroidNativeState& nativeState,
			Eegeo::Rendering::RenderContext& renderContext)
	:m_nativeState(nativeState)
	,m_renderContext(renderContext)
	,m_world(world)
	,m_buttonID(0)
    {
    }

    void PositionJavaPinButtonExample::CreateButton()
    {
    	//get an env for the current thread
    	//
    	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
    	AndroidSafeNativeThreadAttachment attached(m_nativeState);
    	JNIEnv* env = attached.envForThread;

		//get the java HudPinController class
		jstring strClassName = env->NewStringUTF("com/eegeo/examples/HudPinController");
		jclass hudPinControllerClass = m_nativeState.LoadClass(env, strClassName);
		env->DeleteLocalRef(strClassName);

		//create a persistent reference to the class
		m_hudPinControllerClass = static_cast<jclass>(env->NewGlobalRef(hudPinControllerClass));

		//cache the update method as we will call it frequently
		m_updateLocationMethodId = env->GetMethodID(m_hudPinControllerClass, "updatePinButtonScreenLocation", "(IFF)V");

		//get the method to add a pin - only keep a local reference as we wont use again
		jmethodID addJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "addJavaPinButton", "()I");

		//get the constructor for the HudPinController, which takes the activity as a parameter
		jmethodID hudPinControllerConstructor = env->GetMethodID(m_hudPinControllerClass, "<init>", "(Lcom/eegeo/MainActivity;)V");

		//construct an instance of the HudPinController, and create and cache a persistent reference to it.
		//we will make calls on to this instance, and it will add elements to the UI for us form Java.
	    jobject instance = env->NewObject(m_hudPinControllerClass, hudPinControllerConstructor, m_nativeState.activity);
	    m_hudPinController = env->NewGlobalRef(instance);

		//use the addJavaPinButton method on the hudPinController instance to add a pin to the hud.
		//we will get back an integer reference to the pin which we can use to update and remove it later,
		//so cache this
		m_buttonID = env->CallIntMethod(m_hudPinController, addJavaPinButton);
	}

    void PositionJavaPinButtonExample::Suspend()
    {
    	//if we have not started and don't have a pin handle, nothing to do in suspend()
    	if(m_buttonID == 0) {
    		return;
    	}

    	//get an env for the current thread
    	//
    	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
    	AndroidSafeNativeThreadAttachment attached(m_nativeState);
    	JNIEnv* env = attached.envForThread;

    	//get the method to remove a pin, and remove the pin with our cached ID
		jmethodID removeJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "removeJavaPinButton", "(I)V");
		env->CallVoidMethod(m_hudPinController, removeJavaPinButton, m_buttonID);

		//delete the persistent references to the class and object
		env->DeleteGlobalRef(m_hudPinControllerClass);
		env->DeleteGlobalRef(m_hudPinController);

		//reset the pin handle
		m_buttonID = 0;
    }

    void PositionJavaPinButtonExample::Draw()
    {
		//lazily create the pin button when we start drawing so it is not displayed on top of the loading screen
    	if(m_world.Initialising()) {
    		return;
    	}
    	else if(m_buttonID == 0) {
    		CreateButton();
        }

    	//get an env for the current thread
    	//
    	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
    	AndroidSafeNativeThreadAttachment attached(m_nativeState);
    	JNIEnv* env = attached.envForThread;

    	//calculate a screen position for the pin based on an ECEF location (the location of the Tranamerica Pyramid near the start location)
    	const Eegeo::Space::LatLongAltitude pinLocation = Eegeo::Space::LatLongAltitude::FromDegrees(37.795118f, -122.402797f, 0.f);
    	Eegeo::v3 screenPosition;
    	Project(pinLocation, screenPosition);

    	//update the screen position of the pin using the cached update method on the cached object reference to
    	//the pin controller, using the parameters we have calculated and the handle to the pin created earlier
		env->CallVoidMethod(
			m_hudPinController,
			m_updateLocationMethodId,
			m_buttonID,
			screenPosition.GetX(),
			screenPosition.GetY()
		);
    }

    void PositionJavaPinButtonExample::Project (const Eegeo::Space::LatLongAltitude& location, Eegeo::v3& screenPosition)
	{
    	//project a 3D Ecef location to the screen
		Eegeo::m44 finalMatrix;

		Eegeo::m44::Mul (finalMatrix,
				m_renderContext.GetProjectionMatrix(),
				m_renderContext.GetViewMatrix());

		Eegeo::v3 local = (location.ToECEF() - m_renderContext.GetCameraOriginEcef()).ToSingle();
		Eegeo::v4 inVector(local, 1.0f);

		// get clip space coords
		Eegeo::v4 outVector = Eegeo::v4::Mul(inVector, finalMatrix);

		// divide through by w to get normalized device space coords -- range [-1, 1]
		screenPosition.SetX((outVector.GetX()/outVector.GetW()));
		screenPosition.SetY((outVector.GetY()/outVector.GetW()));
		screenPosition.SetZ((outVector.GetZ()/outVector.GetW()));

		// transform from [-1, 1] to [0, 1]
		screenPosition.SetX((screenPosition.GetX() + 1.0f) * 0.5f);
		screenPosition.SetY(1.0f - ((screenPosition.GetY() + 1.0f) * 0.5f));

		float viewport[] = {0, 0, m_renderContext.GetScreenWidth(), m_renderContext.GetScreenHeight()};

		// transform from [0, 1] to screen coords.
		screenPosition.SetX((screenPosition.GetX()*(viewport[2]-viewport[0])) + viewport[0]);
		screenPosition.SetY((screenPosition.GetY()*(viewport[3]-viewport[1])) + viewport[1]);
	}
}
