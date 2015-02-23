// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.aboutpageview;

import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class AboutPageView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private TextView m_aboutTextView = null;

    public AboutPageView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.about_page_layout, m_uiRoot, false);
        m_closeButton = m_view.findViewById(R.id.about_page_view_close_button);
        m_aboutTextView = (TextView)m_view.findViewById(R.id.about_page_view_about_text);

        m_closeButton.setOnClickListener(this);
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayContent(final String content)
    {
        m_aboutTextView.setText(content);
    }

    public void openAboutPage()
    {
        m_closeButton.setEnabled(true);
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
    }

    public void dismissAboutPage()
    {
        m_view.setVisibility(View.GONE);
    }

    public void onClick(View view)
    {
        m_closeButton.setEnabled(false);
        AboutPageViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }
}
