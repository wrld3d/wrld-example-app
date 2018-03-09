// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class QueryContext
{
	private boolean m_isTag;
	private boolean m_tryInterior;
	private boolean m_shouldZoomToBuildingsView;
	private double  m_latitude;
	private double  m_longitude;
	private double  m_altitude;
	private float   m_radius;

	public QueryContext(boolean isTag, boolean tryInterior, boolean shouldZoomToBuildingsView,
						double latitude, double longitude, double altitude,
						float radius)
	{
		m_isTag                     = isTag;
		m_tryInterior               = tryInterior;
		m_shouldZoomToBuildingsView = shouldZoomToBuildingsView;
		m_latitude                  = latitude;
		m_longitude                 = longitude;
		m_altitude                  = altitude;
		m_radius                    = radius;
	}

	public boolean IsTag()                     { return m_isTag; }
	public boolean TryInterior()               { return m_tryInterior; }
	public boolean ShouldZoomToBuildingsView() { return m_shouldZoomToBuildingsView; }
	public double Latitude()                   { return m_latitude; }
	public double Longitude()                  { return m_longitude; }
	public double Altitude()                   { return m_altitude; }
	public float Radius()                      { return m_radius; }
}
