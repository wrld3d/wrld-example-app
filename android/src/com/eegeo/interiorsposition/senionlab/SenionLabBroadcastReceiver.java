package com.eegeo.interiorsposition.senionlab;

import com.eegeo.mapapi.INativeMessageRunner;
import com.senionlab.slutilities.geofencing.interfaces.SLGeometry;
import com.senionlab.slutilities.service.SLBroadcastReceiver;
import com.senionlab.slutilities.type.LocationAvailability;
import com.senionlab.slutilities.type.SLCoordinate3D;
import com.senionlab.slutilities.type.SLHeadingStatus;
import com.senionlab.slutilities.type.SLMotionType;

class SenionLabBroadcastReceiver extends SLBroadcastReceiver
{
    private INativeMessageRunner m_nativeMessageRunner;
    private final long m_nativeCallerPointer;

    public SenionLabBroadcastReceiver(INativeMessageRunner nativeMessageRunner, long nativeCallerPointer)
    {
        m_nativeMessageRunner = nativeMessageRunner;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    @Override
    public void didUpdateLocation(SLCoordinate3D location, double horizontalAccuracyInMeters)
    {
        updateNativeLocation(
                location.getLatitude(),
                location.getLongitude(),
                horizontalAccuracyInMeters,
                location.getFloorNr().intValue());
    }

    @Override
    public void didUpdateLocationAvailability(LocationAvailability locationAvailability)
    {

    }

    @Override
    public void didEnterGeometry(SLGeometry slGeometry)
    {
        updateNativeIsAuthorized(true);
    }

    @Override
    public void didLeaveGeometry(SLGeometry slGeometry)
    {
        updateNativeIsAuthorized(true);
    }

    @Override
    public void didUpdateHeading(double headingInDegrees, SLHeadingStatus headingStatus) {
        if (headingStatus == SLHeadingStatus.CONFIRMED || headingStatus == SLHeadingStatus.PREDICTED) {
            updateNativeHeading(headingInDegrees);
        } else {
            updateNativeIsAuthorized(true);
        }
    }

    @Override
    public void didUpdateMotionType(SLMotionType slMotionType)
    {
        updateNativeIsAuthorized(true);
    }

    @Override
    public void didFinishLoadingManager()
    {
        updateNativeIsAuthorized(true);
    }

    @Override
    public void errorWhileLoadingManager(String s)
    {
        updateNativeIsAuthorized(false);
    }

    @Override
    public void errorWifiNotEnabled()
    {
        updateNativeIsAuthorized(false);
    }

    @Override
    public void errorBleNotEnabled()
    {
        updateNativeIsAuthorized(false);
    }

    private void updateNativeIsAuthorized(final boolean isAuthorized) {
        m_nativeMessageRunner.runOnNativeThread(new Runnable() {
            public void run() {
                SenionLabLocationInteropJniMethods.UpdateIsAuthorized(m_nativeCallerPointer, isAuthorized);
            }
        });
    }

    private void updateNativeLocation(
            final double latitudeDegrees,
            final double longitudeDegrees,
            final double horizontalAccuracyInMeters,
            final int senionFloorNumber) {

        m_nativeMessageRunner.runOnNativeThread(new Runnable() {
            public void run() {
                SenionLabLocationInteropJniMethods.UpdateLocation(
                        m_nativeCallerPointer,
                        latitudeDegrees,
                        longitudeDegrees,
                        horizontalAccuracyInMeters,
                        senionFloorNumber);
            }
        });
    }

    private void updateNativeHeading(final double heading) {
        m_nativeMessageRunner.runOnNativeThread(new Runnable() {
            public void run() {
                SenionLabLocationInteropJniMethods.UpdateHeading(
                        m_nativeCallerPointer,
                        heading);
            }
        });
    }
}
