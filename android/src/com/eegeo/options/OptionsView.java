package com.eegeo.options;

import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class OptionsView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private ToggleButton m_streamOverWifiButton = null;
    private ToggleButton m_dataCachingButton = null;
    private View m_clearCacheButton = null;
    private OptionsCacheClearSubView m_cacheClearSubView = null;

    public OptionsView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.options_layout, m_uiRoot, false);
  
        m_closeButton = m_view.findViewById(R.id.options_view_close_button);
        m_closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				OptionsViewJniMethods.CloseButtonSelected(m_nativeCallerPointer);
			}
		});

        configureStreamOverWifiOption();
        configureDataCachingOption();
        configureClearCacheOption();

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
		
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void openOptions()
    {
        m_closeButton.setEnabled(true);
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
    }

    public void closeOptions()
    {
        m_view.setVisibility(View.GONE);
    }
    
    public void concludeCacheClearCeremony()
    {
    	m_cacheClearSubView.concludeCeremony();
    	m_cacheClearSubView = null;
    }
    
    public boolean isStreamOverWifiOnlySelected()
    {
    	return m_streamOverWifiButton.isChecked();
    }
    
    public boolean isCacheEnabledSelected()
    {
    	return m_dataCachingButton.isChecked();
    }
   
    public void setStreamOverWifiOnlySelected(boolean streamOverWifiOnlySelected)
    {
    	m_streamOverWifiButton.setChecked(streamOverWifiOnlySelected);
    }
   
    public void setCacheEnabledSelected(boolean cacheEnabledSelected)
    {
    	m_dataCachingButton.setChecked(cacheEnabledSelected);
    }
   
    public void setReplayTutorialsSelected(boolean replayTutorialsSelected)
    {
        // To be implemented in the future.
        // Currently only available in windows.
    }

    private void configureStreamOverWifiOption()
    {
        View.OnClickListener streamOverWifiClickListener = new View.OnClickListener() {
			public void onClick(View arg0) {
				if(!(arg0 instanceof ToggleButton)) {
					m_streamOverWifiButton.setChecked(!m_streamOverWifiButton.isChecked());
				}
				OptionsViewJniMethods.StreamOverWifiToggled(m_nativeCallerPointer);
			}
        };
        
        m_streamOverWifiButton = (ToggleButton) m_view.findViewById(R.id.options_view_stream_wifi_only_togglebutton);
        m_streamOverWifiButton.setOnClickListener(streamOverWifiClickListener);
        TextView streamOverWifiLabel = (TextView) m_view.findViewById(R.id.options_view_stream_wifi_only_label);
        streamOverWifiLabel.setOnClickListener(streamOverWifiClickListener);
    }
    
    private void configureDataCachingOption()
    {
        View.OnClickListener dataCachingButtonClickListener = new View.OnClickListener() {
			public void onClick(View arg0) {
				if(!(arg0 instanceof ToggleButton)) {
					m_dataCachingButton.setChecked(!m_dataCachingButton.isChecked());
				}
				OptionsViewJniMethods.CachingEnabledToggled(m_nativeCallerPointer);
			}
		};
        m_dataCachingButton = (ToggleButton) m_view.findViewById(R.id.options_view_cache_enabled_togglebutton);
        m_dataCachingButton.setOnClickListener(dataCachingButtonClickListener);
        TextView cacheEnabledLabel = (TextView) m_view.findViewById(R.id.options_view_cache_enabled_label);
        cacheEnabledLabel.setOnClickListener(dataCachingButtonClickListener);
    }
    
    private void configureClearCacheOption()
    {
        View.OnClickListener clearCacheClickListener = new View.OnClickListener() {
			public void onClick(View arg0) {
				beginCacheClearCeremony();
			}
		};
        m_clearCacheButton = m_view.findViewById(R.id.options_view_clear_cache_button);
        m_clearCacheButton.setOnClickListener(clearCacheClickListener);
        TextView clearCacheLabel = (TextView) m_view.findViewById(R.id.options_view_clear_cache_label);
        clearCacheLabel.setOnClickListener(clearCacheClickListener);
    }
    
    private void beginCacheClearCeremony()
    {
    	assert(m_cacheClearSubView == null);
        m_cacheClearSubView = new OptionsCacheClearSubView(m_activity);
        
    	m_cacheClearSubView.displayWarning(new Runnable() {
    		public void run() {
    			OptionsViewJniMethods.ClearCacheSelected(m_nativeCallerPointer);
    		}
    	});
    }
}
