package com.eegeo.menu;

import org.json.JSONObject;

public class MenuItemData
{
	private String m_text;
	private String m_icon;
	
	public MenuItemData(String text, String icon)
	{
		m_text = text;
		m_icon = icon;
	}
	
	public String getText()
	{
		return m_text;
	}
	
	public String getIcon()
	{
		return m_icon;
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
			
			return new MenuItemData(itemText, itemIcon);
		}
		catch (Exception e)
		{
			return null;
		}
	}
}
