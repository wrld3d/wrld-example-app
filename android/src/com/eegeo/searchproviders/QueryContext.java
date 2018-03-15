// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class QueryContext
{
	private boolean m_isTag;
	private String  m_tagText;
	private boolean m_tryInterior;
	private boolean m_shouldZoomToBuildingsView;
	private boolean m_usesLocationAndRadius;
	private double  m_latitude;
	private double  m_longitude;
	private double  m_altitude;
	private float   m_radius;

	public QueryContext(boolean isTag, String tagText,
						boolean tryInterior, boolean shouldZoomToBuildingsView)
	{
		m_isTag                     = isTag;
		m_tagText                   = tagText;
		m_tryInterior               = tryInterior;
		m_shouldZoomToBuildingsView = shouldZoomToBuildingsView;

		m_usesLocationAndRadius     = false;
		m_latitude                  = 0;
		m_longitude                 = 0;
		m_altitude                  = 0;
		m_radius                    = 0;
	}

	public QueryContext(boolean isTag, String tagText,
						boolean tryInterior, boolean shouldZoomToBuildingsView,
						double latitude, double longitude, double altitude,
						float radius)
	{
		m_isTag                     = isTag;
		m_tagText                   = tagText;
		m_tryInterior               = tryInterior;
		m_shouldZoomToBuildingsView = shouldZoomToBuildingsView;

		m_usesLocationAndRadius     = true;
		m_latitude                  = latitude;
		m_longitude                 = longitude;
		m_altitude                  = altitude;
		m_radius                    = radius;
	}

	public boolean IsTag()                     { return m_isTag; }
	public String TagText()                    { return m_tagText; }
	public boolean TryInterior()               { return m_tryInterior; }
	public boolean ShouldZoomToBuildingsView() { return m_shouldZoomToBuildingsView; }

	public boolean UsesLocationAndRadius()     { return m_usesLocationAndRadius; }
	public double Latitude()                   { return m_latitude; }
	public double Longitude()                  { return m_longitude; }
	public double Altitude()                   { return m_altitude; }
	public float Radius()                      { return m_radius; }
}
