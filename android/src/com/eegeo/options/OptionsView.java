package com.eegeo.options;

import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.CompoundButton;

import com.eegeo.mobileexampleapp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;

public class OptionsView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private CompoundButton m_streamOverWifiButton = null;
    private CompoundButton m_dataCachingButton = null;
    private View m_clearCacheButton = null;
    private View m_playTutorialAgainButton = null;
    private OptionsCacheClearSubView m_cacheClearSubView = null;
    private OptionsMessage m_messageView = null;

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
        configurePlayTutorialAgainOption();

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

    private void ToggleButton(CompoundButton button)
    {
        button.setChecked(!button.isChecked());
    }

    public void openClearCacheWarning()
    {
        assert(m_cacheClearSubView == null);
        m_cacheClearSubView = new OptionsCacheClearSubView(m_activity, m_nativeCallerPointer);

        m_cacheClearSubView.displayWarning(new Runnable() {
            public void run() {
                OptionsViewJniMethods.ClearCacheTriggered(m_nativeCallerPointer);
            }
        });
    }

    private void configureStreamOverWifiOption()
    {
        m_streamOverWifiButton = (CompoundButton) m_view.findViewById(R.id.options_view_stream_wifi_only_togglebutton);
        m_streamOverWifiButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0)
            {
                OptionsViewJniMethods.StreamOverWifiToggled(m_nativeCallerPointer);
            }
        });
        TextView streamOverWifiLabel = (TextView) m_view.findViewById(R.id.options_view_stream_wifi_only_label);
        streamOverWifiLabel.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0)
            {
                ToggleButton(m_streamOverWifiButton);
                OptionsViewJniMethods.StreamOverWifiToggled(m_nativeCallerPointer);
            }
        });
    }
    
    private void configureDataCachingOption()
    {
        m_dataCachingButton = (CompoundButton) m_view.findViewById(R.id.options_view_cache_enabled_togglebutton);
        m_dataCachingButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0)
            {
                OptionsViewJniMethods.CachingEnabledToggled(m_nativeCallerPointer);
            }
        });
        TextView cacheEnabledLabel = (TextView) m_view.findViewById(R.id.options_view_cache_enabled_label);
        cacheEnabledLabel.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0)
            {
                ToggleButton(m_dataCachingButton);
                OptionsViewJniMethods.CachingEnabledToggled(m_nativeCallerPointer);
            }
        });
    }

    private void configureClearCacheOption()
    {
        View.OnClickListener clearCacheClickListener = new View.OnClickListener() {
            public void onClick(View arg0)
            {
                OptionsViewJniMethods.ClearCacheSelected(m_nativeCallerPointer);
            }
        };
        m_clearCacheButton = (View) m_view.findViewById(R.id.options_view_clear_cache_button);
        m_clearCacheButton.setOnClickListener(clearCacheClickListener);
        TextView clearCacheLabel = (TextView) m_view.findViewById(R.id.options_view_clear_cache_label);
        clearCacheLabel.setOnClickListener(clearCacheClickListener);
    }

    private void configurePlayTutorialAgainOption()
    {
        View.OnClickListener playTutorialAgainClickListener = new View.OnClickListener() {
            public void onClick(View arg0)
            {
                OptionsViewJniMethods.PlayTutorialAgainSelected(m_nativeCallerPointer);

                ShowMessage(stringResource(R.string.options_view_replay_title),
                            stringResource(R.string.options_view_replay_message));
            }
        };
        m_playTutorialAgainButton = (View) m_view.findViewById(R.id.options_view_playtutorial_button);
        m_playTutorialAgainButton.setOnClickListener(playTutorialAgainClickListener);
        TextView playTutorialAgainLabel = (TextView) m_view.findViewById(R.id.options_view_playtutorial_label);
        playTutorialAgainLabel.setOnClickListener(playTutorialAgainClickListener);
    }

    private void ShowMessage(String title, String message)
    {
        assert(m_messageView == null);
        m_messageView = new OptionsMessage(m_activity, title, message,
                new OptionsMessage.OnClose()
                {
                    public void call()
                    {
                        m_messageView = null;

                        OptionsViewJniMethods.CloseButtonSelected(m_nativeCallerPointer);
                    }
                });
    }

    private String stringResource(int resourceId)
    {
        return m_activity.getResources().getString(resourceId);
    }
}
