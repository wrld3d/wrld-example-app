package com.eegeo.menu;

import org.json.JSONObject;

public class MenuItemData
{
	private String m_text;
	private String m_details;
	private String m_icon;
	
	public MenuItemData(String text, String details, String icon)
	{
		m_text = text;
		m_details = details;
		m_icon = icon;
	}
	
	public String getText()
	{
		return m_text;
	}
	
	public String getDetails()
	{
		return m_details;
	}
	
	public String getIcon()
	{
		return m_icon;
	}
	
	public boolean hasDetails()
	{
		return m_details != "";
	}
	
	public static MenuItemData fromJson(String serialisedJson)
	{
		try
		{
			JSONObject json = new JSONObject(serialisedJson);
			String itemText = json.getString("name");
			String itemIcon = "";
			
			if (json.has("icon"))
			{
				itemIcon = json.getString("icon");
			}
			
			String itemDetails = "";
			if (json.has("details"))
			{
				itemDetails = json.getString("details");
			}
			
			return new MenuItemData(itemText, itemDetails, itemIcon);
		}
		catch (Exception e)
		{
			return null;
		}
	}
}
