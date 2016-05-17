package com.eegeo.helpers;

import com.eegeo.mobileexampleapp.R;

import android.view.View;

public class TintablePinToggleButton 
{
	private View m_view;
	private boolean m_isPinned;
	
    public TintablePinToggleButton(View view) 
    {
    	m_view = view;
    	m_isPinned = false;
	}
    
    public boolean isPinned() 
    { 
    	return m_isPinned; 
    } 

    public void setPinToggleState(boolean isPinned)
	{
		m_isPinned = isPinned;
		int displayed = m_isPinned ? R.id.toggle_pinned_control_pinned : R.id.toggle_pinned_control_unpinned;
		int hidden = m_isPinned ? R.id.toggle_pinned_control_unpinned : R.id.toggle_pinned_control_pinned;
		m_view.findViewById(displayed).setVisibility(View.VISIBLE);
		m_view.findViewById(hidden).setVisibility(View.INVISIBLE);
	}
}
