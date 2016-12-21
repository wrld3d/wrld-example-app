package com.eegeo.senion;

import java.util.ArrayList;

import android.content.Context;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.senionlab.slutilities.geofencing.interfaces.SLGeometry;
import com.senionlab.slutilities.service.SLBroadcastReceiver;
import com.senionlab.slutilities.service.SLConsumer;
import com.senionlab.slutilities.service.SLServiceManager;
import com.senionlab.slutilities.type.FloorNr;
import com.senionlab.slutilities.type.SLCoordinate3D;
import com.senionlab.slutilities.type.SLHeadingStatus;
import com.senionlab.slutilities.type.SLIndoorLocationException;
import com.senionlab.slutilities.type.SLLocationState;
import com.senionlab.slutilities.type.SLLocationStatus;
import com.senionlab.slutilities.type.SLMotionType;

public class SenionLabLocationManager implements SLConsumer 
{
	private SLServiceManager m_serviceManager;
	private boolean m_firstTimeBound = true;
	private MainActivity m_activity;
	private long m_nativeCallerPointer;
	boolean m_isServiceBound = false;
	
	public SenionLabLocationManager(MainActivity activity, 
									long nativeCallerPointer) 
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;
		m_serviceManager = SLServiceManager.getInstance(m_activity);
	}

	public void StopUpdatingLocation() 
	{
		try 
		{
			if(m_isServiceBound) 
			{
				m_serviceManager.unbindService(this);
				m_isServiceBound = false;
			}
			m_serviceManager.unregisterReceiver(receiver);
			m_serviceManager.stop();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public void StartUpdatingLocation(String mapKey, 
									  String customerId) 
	{
		try 
		{
			m_serviceManager.registerReceiver(receiver);
			m_serviceManager.bindService(SenionLabLocationManager.this);
			m_isServiceBound = true;
			m_serviceManager.start(mapKey,customerId);
			
			// For mock testing
//			StartSenionMockTesting(mapKey, customerId);
		} 
		catch (SLIndoorLocationException e) 
		{
			e.printStackTrace();
		}	
	}

	public void didBindToService() 
	{
		if (m_firstTimeBound) 
		{
			didBindAndLoad();
		}
		m_firstTimeBound = false;
	}

	private void didBindAndLoad() 
	{
	}

	private void StartSenionMockTesting(String mapKey, String customerId)
	{
		int floorIndex = 0;   // for mock testing only
	    
//	    if(m_pBuildingID.Value() == "westport_house")
	    {
	        // West Port Mock Data
	        SLCoordinate3D coordinate3d1 =  new SLCoordinate3D(56.459875,-2.978198, new FloorNr(floorIndex));
	        SLLocationState locState1 = new SLLocationState(coordinate3d1, 0.0, SLLocationStatus.CONFIRMED);
	        
	        SLCoordinate3D coordinate3d2 =  new SLCoordinate3D(56.459959,-2.978228, new FloorNr(floorIndex));
	        SLLocationState locState2 = new SLLocationState(coordinate3d2, 0.0, SLLocationStatus.CONFIRMED);
	        
	        SLCoordinate3D coordinate3d3 =  new SLCoordinate3D(56.460009,-2.978240, new FloorNr(floorIndex));
	        SLLocationState locState3 = new SLLocationState(coordinate3d3, 0.0, SLLocationStatus.CONFIRMED);
	        
	        SLCoordinate3D coordinate3d4 =  new SLCoordinate3D(56.460046,-2.978339, new FloorNr(floorIndex));
	        SLLocationState locState4 = new SLLocationState(coordinate3d4, 0.0, SLLocationStatus.CONFIRMED);
	        
	        ArrayList<SLLocationState> locationStateArry = new ArrayList<SLLocationState>();
	        locationStateArry.add(locState1);
	        locationStateArry.add(locState2);
	        locationStateArry.add(locState3);
	        locationStateArry.add(locState4);
	        
	        m_serviceManager.startMockupLocation(mapKey, customerId, locationStateArry);
	    }	
	}

	private SLBroadcastReceiver receiver = new SLBroadcastReceiver() 
	{

		public void didUpdateLocation(SLCoordinate3D location, double uncertaintyRadius, SLLocationStatus status) 
		{
			synchronized (this) 
			{
				SenionLabLocationJniMethods.OnLocationChanged(m_nativeCallerPointer, 
															  location.getLatitude(), 
															  location.getLongitude(), 
															  location.getFloorNr().integerValue().toString());
			}
		}

		public void didUpdateMotionType(SLMotionType motionType) 
		{
		}

		public void didUpdateHeading(double heading, SLHeadingStatus status) 
		{
		}

		public void didFinishLoadingManager() 
		{
		}

		public void errorWhileLoadingManager(String errorMsg) 
		{
		}

		public void errorWifiNotEnabled() 
		{
		}

		public void errorBleNotEnabled() 
		{
		}

		public void didEnterGeometry(final SLGeometry geometry) 
		{	
		}

		public void didLeaveGeometry(final SLGeometry geometry) 
		{
		}
	};

	@Override
	public Context getContext() 
	{
		return m_activity;
	}
}
