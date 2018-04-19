// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class QueryContext
{
	private boolean m_clearPreviousResults;
	private boolean m_isTag;
	private String  m_tagText;
	private boolean m_tryInterior;

	private boolean m_usesLocation;
	private double  m_latitude;
	private double  m_longitude;
	private double  m_altitude;

	private boolean m_usesRadius;
	private float   m_radius;

	public QueryContext(boolean clearPreviousResults,
						boolean isTag, String tagText,
						boolean tryInterior)
	{
		m_clearPreviousResults = clearPreviousResults;
		m_isTag                = isTag;
		m_tagText              = tagText;
		m_tryInterior          = tryInterior;

		m_usesLocation         = false;
		m_latitude             = 0;
		m_longitude            = 0;
		m_altitude             = 0;

		m_usesRadius           = false;
		m_radius               = 0;
	}

	public QueryContext(boolean clearPreviousResults,
						boolean isTag, String tagText,
						boolean tryInterior,
						float radius)
	{
		m_clearPreviousResults = clearPreviousResults;
		m_isTag                = isTag;
		m_tagText              = tagText;
		m_tryInterior          = tryInterior;

		m_usesLocation         = false;
		m_latitude             = 0;
		m_longitude            = 0;
		m_altitude             = 0;

		m_usesRadius           = true;
		m_radius               = radius;
	}

	public QueryContext(boolean clearPreviousResults,
						boolean isTag, String tagText,
						boolean tryInterior,
						double latitude, double longitude, double altitude,
						float radius)
	{
		m_clearPreviousResults = clearPreviousResults;
		m_isTag                = isTag;
		m_tagText              = tagText;
		m_tryInterior          = tryInterior;

		m_usesLocation         = true;
		m_latitude             = latitude;
		m_longitude            = longitude;
		m_altitude             = altitude;

		m_usesRadius                = true;
		m_radius                    = radius;
	}

	public boolean ClearPreviousResults() { return m_clearPreviousResults; }
	public boolean IsTag()                { return m_isTag; }
	public String TagText()               { return m_tagText; }
	public boolean TryInterior()          { return m_tryInterior; }

	public boolean UsesLocation()         { return m_usesLocation; }
	public double Latitude()              { return m_latitude; }
	public double Longitude()             { return m_longitude; }
	public double Altitude()              { return m_altitude; }

	public boolean UsesRadius()           { return m_usesRadius; }
	public float Radius()                 { return m_radius; }
}
