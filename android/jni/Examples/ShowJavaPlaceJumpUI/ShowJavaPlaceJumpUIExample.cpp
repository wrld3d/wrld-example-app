/*
 * ShowJavaPlaceJumpUIExample.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: kimbleoperations
 */

#include <jni.h>
#include "ShowJavaPlaceJumpUIExample.h"
#include "ICameraJumpController.h"

namespace Examples
{
	//this is the native companion type to com.eegeo.examples.PlaceJumpMenu.java
	//
	ShowJavaPlaceJumpUIExample::ShowJavaPlaceJumpUIExample(
			AndroidNativeState& nativeState,
			Eegeo::Camera::ICameraJumpController& cameraJumpController
			)
	: m_nativeState(nativeState)
	, m_cameraJumpController(cameraJumpController)
	, m_pTargetLocation(NULL)
    {
		m_locations["NYC"] = ViewLocation(40.703762, -74.013733, 0, 240.0f, 1800.0f);
		m_locations["London"] = ViewLocation(51.506172,-0.118915, 0, 351.0f, 2731.0f);
		m_locations["SF"] = ViewLocation(37.7858,-122.401, 0.0, 0.0, 1781.0);
		m_locations["Kyoto"] = ViewLocation(34.9977166,135.755402, 0, 0.0f, 1500.0f);
		m_locations["Melbourne"] = ViewLocation(-37.815005, 144.964415, 0, 0.0f, 1500.0f);
    }

    void ShowJavaPlaceJumpUIExample::Start()
    {
        pthread_mutex_init(&m_mutex, 0);

		//get an env for the current thread
		//
		//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* env = attached.envForThread;

		//get the java HudPinController class
		jstring strClassName = env->NewStringUTF("com/eegeo/examples/PlaceJumpMenu");
		jclass placeJumpMenuClass = m_nativeState.LoadClass(env, strClassName);
		env->DeleteLocalRef(strClassName);

		//create a persistent reference to the class
		m_placeJumpMenuClass = static_cast<jclass>(env->NewGlobalRef(placeJumpMenuClass));

		//get the constructor for the HudPinController, which takes the activity as a parameter
		jmethodID placeJumpMenuClassConstructor = env->GetMethodID(m_placeJumpMenuClass, "<init>", "(Lcom/eegeo/MainActivity;)V");

		//construct an instance of the PlaceJumpMenu, and create and cache a persistent reference to it.
		//we will make calls on to this instance, and it will add elements to the UI for us from Java.
		//we can later use this cached reference to destroy the UI
	    jobject instance = env->NewObject(m_placeJumpMenuClass, placeJumpMenuClassConstructor, m_nativeState.activity);
	    m_placeJumpMenu = env->NewGlobalRef(instance);

	    //get the showVisitMenu method, and call it on the instance we have created - the 'J'
	    //argument refers to a long - we will carriage a pointer to this so we can be called
	    //back by the java code when a menu item is selected
		jmethodID showVisitMenu = env->GetMethodID(m_placeJumpMenuClass, "showVisitMenu", "(J)V");

		jlong pointerToThis = (jlong)(this);
		env->CallVoidMethod(m_placeJumpMenu, showVisitMenu, pointerToThis);
    }

    void ShowJavaPlaceJumpUIExample::Suspend()
	{
		//get an env for the current thread
		//
		//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* env = attached.envForThread;

		//get the method to remove the menu, and remove menu
		jmethodID removeMenu = env->GetMethodID(m_placeJumpMenuClass, "removeVisitMenu", "()V");
		env->CallVoidMethod(m_placeJumpMenu, removeMenu);

		//delete the persistent references to the class and object
		env->DeleteGlobalRef(m_placeJumpMenuClass);
		env->DeleteGlobalRef(m_placeJumpMenu);

	    pthread_mutex_destroy(&m_mutex);
	}

    void ShowJavaPlaceJumpUIExample::Update(float dt)
    {
        pthread_mutex_lock(&m_mutex);
        if(m_pTargetLocation != NULL)
        {
        	m_cameraJumpController.JumpTo(m_pTargetLocation->location, m_pTargetLocation->heading, m_pTargetLocation->distance);
        	m_pTargetLocation = NULL;
        }
        pthread_mutex_unlock(&m_mutex);
    }

    void ShowJavaPlaceJumpUIExample::JumpToLocation(const std::string& location)
    {
        pthread_mutex_lock(&m_mutex);
    	m_pTargetLocation = &m_locations[location];
        pthread_mutex_unlock(&m_mutex);
    }
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_PlaceJumpMenu_visitLocation(JNIEnv* jenv, jobject obj, jlong nativeObjectPtr, jstring location)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(location, 0);
	std::string locationString = chars;
	jenv->ReleaseStringUTFChars(location, chars);

	//call back into our example instance
	Examples::ShowJavaPlaceJumpUIExample* example = (Examples::ShowJavaPlaceJumpUIExample*)(nativeObjectPtr);
	example->JumpToLocation(locationString);
}

