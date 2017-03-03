package com.eegeo.interiorsposition.senionlab;

import com.senionlab.slutilities.geofencing.interfaces.SLGeometry;
import com.senionlab.slutilities.service.SLBroadcastReceiver;
import com.senionlab.slutilities.type.LocationAvailability;
import com.senionlab.slutilities.type.LocationSource;
import com.senionlab.slutilities.type.SenionLocationSource;

import com.senionlab.slutilities.type.SLCoordinate3D;
import com.senionlab.slutilities.type.SLHeadingStatus;
import com.senionlab.slutilities.type.SLMotionType;

class SenionLabBroadcastReceiver extends SLBroadcastReceiver
{
    private final Object m_errorLock = new Object();
    private final Object m_updateLock = new Object();
    private long m_nativeCallerPointer;
    private SenionLabLocationManager m_locationManager;

    public SenionLabBroadcastReceiver(SenionLabLocationManager locationManager, long nativeCallerPointer)
    {
        m_nativeCallerPointer = nativeCallerPointer;
        m_locationManager = locationManager;
        m_locationManager.registerReceiver(this);
    }

    public void destroy()
    {
        m_locationManager.unregisterReceiver(this);
    }

    @Override
    public void didUpdateLocation(SLCoordinate3D location, double v, LocationSource locationSource)
    {
        synchronized (m_updateLock)
        {
            SenionLabBroadcastReceiverJniMethods.DidUpdateLocation(m_nativeCallerPointer,
                                                                   location.getLatitude(),
                                                                   location.getLongitude(),
                                                                   location.getFloorNr().intValue());
            
            if(locationSource instanceof SenionLocationSource)
            {
            	SenionLocationSource senionLocationSource = ((SenionLocationSource) locationSource);
            	SenionLabBroadcastReceiverJniMethods.SetInteriorIdFromMapKey(m_nativeCallerPointer, senionLocationSource.getMapKey());
            }
        }
    }
    
    @Override
    public void didUpdateLocationAvailability(LocationAvailability locationAvailability)
    {
    	boolean available = locationAvailability == LocationAvailability.AVAILABLE;
    	SenionLabBroadcastReceiverJniMethods.SetIsConnected(m_nativeCallerPointer, available);
    	m_locationManager.updateAvailability(available);
    }

    @Override
    public void didEnterGeometry(SLGeometry slGeometry)
    {
        didLocationError(false);
    }

    @Override
    public void didLeaveGeometry(SLGeometry slGeometry)
    {
        didLocationError(false);
    }

    @Override
    public void didUpdateHeading(double v, SLHeadingStatus slHeadingStatus)
    {
        didLocationError(false);
    }

    @Override
    public void didUpdateMotionType(SLMotionType slMotionType)
    {
        didLocationError(false);
    }

    @Override
    public void didFinishLoadingManager()
    {
        didLocationError(false);
    }

    @Override
    public void errorWhileLoadingManager(String s)
    {
        didLocationError(true);
    }

    @Override
    public void errorWifiNotEnabled()
    {
        didLocationError(true);
    }

    @Override
    public void errorBleNotEnabled()
    {
        didLocationError(true);
    }

    private void didLocationError(final boolean didError)
    {
        synchronized (m_errorLock)
        {
            SenionLabBroadcastReceiverJniMethods.SetIsAuthorized(m_nativeCallerPointer, !didError);
        }
    }
}
