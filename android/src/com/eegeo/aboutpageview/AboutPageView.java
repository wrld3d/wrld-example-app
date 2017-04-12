// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.aboutpageview;

import android.support.v4.content.ContextCompat;
import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class AboutPageView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private TextView m_aboutTextView = null;
    private TextView m_eulaLink = null;
    private TextView m_privacyLink = null;
    private TextView m_legalLink = null;
    private TextView m_teamLink = null;
    private ImageView m_logoImage = null;

    public AboutPageView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.about_page_layout, m_uiRoot, false);
        m_closeButton = m_view.findViewById(R.id.about_page_view_close_button);
        m_aboutTextView = (TextView)m_view.findViewById(R.id.about_page_view_about_text);
        m_eulaLink = (TextView)m_view.findViewById(R.id.about_page_view_about_text_eula_link);
        m_privacyLink = (TextView)m_view.findViewById(R.id.about_page_view_privacy_link);
        m_legalLink = (TextView)m_view.findViewById(R.id.about_page_view_legal_link);
        m_teamLink = (TextView)m_view.findViewById(R.id.about_page_view_team_link);
        m_logoImage = (ImageView)m_view.findViewById(R.id.about_page_eegeo_logo);
        
        RelativeLayout.LayoutParams layoutParams = (LayoutParams) m_view.getLayoutParams();
        if (m_activity.getResources().getBoolean(R.bool.isPhone)) 
        {
            layoutParams.topMargin = layoutParams.bottomMargin = layoutParams.leftMargin = layoutParams.rightMargin = m_activity.dipAsPx(20);
        }
        else 
        {
            layoutParams.topMargin = layoutParams.bottomMargin = m_activity.dipAsPx(80);
            layoutParams.leftMargin = layoutParams.rightMargin = (int) (m_uiRoot.getWidth() * 0.3f);
        }

        m_logoImage.setOnLongClickListener(new View.OnLongClickListener()
        {
            @Override
            public boolean onLongClick(View v)
            {
                showHiddenText();
                return true;
            }
        });

        m_closeButton.setOnClickListener(this);
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_eulaLink.setMovementMethod(LinkMovementMethod.getInstance());
        m_privacyLink.setMovementMethod(LinkMovementMethod.getInstance());
        m_legalLink.setMovementMethod(LinkMovementMethod.getInstance());
        m_teamLink.setMovementMethod(LinkMovementMethod.getInstance());
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayContent(final String content)
    {
        m_aboutTextView.setText(content);
    }

    public void showHiddenText()
    {
        AboutPageViewJniMethods.LogoLongPress(m_nativeCallerPointer);
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
