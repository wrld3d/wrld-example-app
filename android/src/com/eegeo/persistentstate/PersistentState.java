// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.persistentstate;

import android.content.Context;
import android.content.SharedPreferences;

import com.eegeo.entrypointinfrastructure.MainActivity;

public class PersistentState
{
    private MainActivity m_activity = null;
    private SharedPreferences m_sharedPref;
    private SharedPreferences.Editor m_editor;

    public PersistentState(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_sharedPref = m_activity.getPreferences(Context.MODE_PRIVATE);
        m_editor = m_sharedPref.edit();
    }

    public boolean containsKey(String key)
    {
        return m_sharedPref.contains(key);
    }

    public boolean getBoolean(String key)
    {
        return (Boolean) m_sharedPref.getAll().get(key);
    }

    public int getInt(String key)
    {
        return (Integer) m_sharedPref.getAll().get(key);
    }

    public double getDouble(String key)
    {
        return ((Float) m_sharedPref.getAll().get(key)).doubleValue();
    }

    public String getString(String key)
    {
        return (String) m_sharedPref.getAll().get(key);
    }

    public void setBoolean(String key, boolean value)
    {
        m_editor.putBoolean(key, value);
        m_editor.commit();
    }

    public void setInt(String key, int value)
    {
        m_editor.putInt(key, value);
        m_editor.commit();
    }

    public void setDouble(String key, double value)
    {
        m_editor.putFloat(key, (float)value);
        m_editor.commit();
    }

    public void setString(String key, String value)
    {
        m_editor.putString(key, value);
        m_editor.commit();
    }

    public void clearAll()
    {
        m_editor = m_sharedPref.edit();
        m_editor.clear();
        m_editor.commit();
    }
}
