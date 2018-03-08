// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class QueryContext
{
	private boolean m_isTag;
	private boolean m_tryInterior;
	private double  m_latitude;
	private double  m_longitude;
	private double  m_altitude;
	private float   m_radius;

	public QueryContext(boolean isTag, boolean tryInterior,
						double latitude, double longitude, double altitude,
						float radius)
	{
		m_isTag       = isTag;
		m_tryInterior = tryInterior;
		m_latitude    = latitude;
		m_longitude   = longitude;
		m_altitude    = altitude;
		m_radius      = radius;
	}

	public boolean GetIsTag()       { return m_isTag; }
	public boolean GetTryInterior() { return m_tryInterior; }
	public double GetLatitude()     { return m_latitude; }
	public double GetLongitude()    { return m_longitude; }
	public double GetAltitude()     { return m_altitude; }
	public float GetRadius()        { return m_radius; }
}
