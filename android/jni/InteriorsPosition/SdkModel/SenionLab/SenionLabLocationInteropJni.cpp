#include "SenionLabLocationInteropJni.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SenionLabLocationInterop.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateIsAuthorized(
        JNIEnv *jenv,
        jclass clazz,
        jlong nativeObjectPtr,
        jboolean isAuthorized)
    {
        ASSERT_NATIVE_THREAD

        using ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationInterop;
        auto* pSenionInterop = reinterpret_cast<SenionLabLocationInterop*>(nativeObjectPtr);

        pSenionInterop->UpdateIsAuthorized(isAuthorized);
    }

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateLocation(
            JNIEnv *jenv,
            jclass clazz,
            jlong nativeObjectPtr,
            jdouble latitudeDegrees,
            jdouble longitudeDegrees,
            jdouble horizontalAltitude,
            jint senionFloorNumber)
    {
        ASSERT_NATIVE_THREAD

        using ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationInterop;
        auto* pSenionInterop = reinterpret_cast<SenionLabLocationInterop*>(nativeObjectPtr);

        pSenionInterop->UpdateLocation(
                latitudeDegrees,
                longitudeDegrees,
                horizontalAltitude,
                senionFloorNumber);
    }

    JNIEXPORT void JNICALL Java_com_eegeo_interiorsposition_senionlab_SenionLabLocationInteropJniMethods_UpdateHeading(
        JNIEnv *jenv,
        jclass clazz,
        jlong nativeObjectPtr,
        jdouble headingInDegrees)
    {
        ASSERT_NATIVE_THREAD

        using ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationInterop;
        auto* pSenionInterop = reinterpret_cast<SenionLabLocationInterop*>(nativeObjectPtr);

        pSenionInterop->UpdateHeading(headingInDegrees);
    }

}
