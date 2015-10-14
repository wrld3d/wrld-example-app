//Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.watermark;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.view.View;
import android.widget.RelativeLayout;

public class WatermarkView implements View.OnClickListener
{
 private MainActivity m_activity = null;
 private long m_nativeCallerPointer;
 private String m_googleAnalyticsReferrerToken;
 private View m_view = null;
 private static AlertDialog m_options = null;

 private float m_yPosActive;
 private float m_yPosInactive;

 private final long m_stateChangeAnimationTimeMilliseconds = 200;

 public WatermarkView(MainActivity activity, long nativeCallerPointer, String googleAnalyticsReferrerToken)
 {
     m_activity = activity;
     m_nativeCallerPointer = nativeCallerPointer;
     m_googleAnalyticsReferrerToken = googleAnalyticsReferrerToken;

     final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
     m_view = m_activity.getLayoutInflater().inflate(R.layout.watermark_layout, uiRoot, false);

     m_view.setOnClickListener(this);
     
     m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
     {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{   
		        final float screenHeight = uiRoot.getHeight();
		        final float screenWidth = uiRoot.getWidth();
		        final float viewHeight = m_view.getHeight();
		        final float viewWidth = m_view.getWidth();
		        
		        if(m_activity.getResources().getBoolean(R.bool.isPhone))
		        {
		            m_yPosActive = m_activity.dipAsPx(20);
		            m_yPosInactive = (-viewHeight);

			        m_view.setX((screenWidth*0.5f) - (viewWidth*0.5f));
		        }
		        else
		        {
		            m_yPosActive = (screenHeight - viewHeight) - m_activity.dipAsPx(8);
		            m_yPosInactive = (screenHeight + viewHeight);

			        m_view.setX((screenWidth - viewWidth) - m_activity.dipAsPx(8));
		        }

		        m_view.setY(m_yPosInactive);
		        m_view.removeOnLayoutChangeListener(this);
			}
     });
     
     m_view.setAlpha(0.8f);
     uiRoot.addView(m_view);
 }

 public void destroy()
 {
     if(m_options != null)
     {
         m_options.dismiss();
         m_options = null;
     }
     
     final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
     uiRoot.removeView(m_view);
     m_view = null;
 }

 @Override
 public void onClick(View view)
 {
     AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);

     String appName =  m_activity.getPackageManager().getApplicationLabel(m_activity.getApplicationInfo()).toString();
    	  
     builder.setTitle("Maps by eeGeo");
     builder.setMessage("The " + appName + " app is open source. It's built using the eeGeo maps SDK, a cross platform API for building engaging, customizable apps");
     builder.setPositiveButton("Find Out More", createClickListener(true));
     builder.setNegativeButton("Later", createClickListener(false));
     builder.setCancelable(false);

     m_options = builder.show();
	 WatermarkViewJniMethods.OnSelected(m_nativeCallerPointer);
 }

 public void animateToActive()
 {
     animateViewToY((int)m_yPosActive);
 }

 public void animateToInactive()
 {
     animateViewToY((int)m_yPosInactive);
 }

 protected void animateViewToY(final int yAsPx)
 {
     m_view.animate()
     .y(yAsPx)
     .setDuration(m_stateChangeAnimationTimeMilliseconds);
 }

 public void animateToIntermediateOnScreenState(final float onScreenState)
 {
     int viewYPx = (int)m_view.getY();
     int newYPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

     if(viewYPx != newYPx)
     {
         m_view.setY(newYPx);
     }
 }
 
 private DialogInterface.OnClickListener createClickListener(final boolean shouldPreload)
 {
     return new DialogInterface.OnClickListener()
     {
         @Override
         public void onClick(DialogInterface dialog, int which)
         {
             handleSelection(shouldPreload);
         }
     };
 }

 private void handleSelection(final boolean shouldOpenLink)
 {
	 if(shouldOpenLink)
	 {
		String url = "http://eegeo.com/findoutmore?utm_source=" + m_googleAnalyticsReferrerToken + "&utm_medium=referral&utm_campaign=eegeo";
	 	final Uri uri = Uri.parse(url);
	 	final Intent browserIntent = new Intent(Intent.ACTION_VIEW, uri);
	 	m_activity.startActivity(browserIntent);
	 }
	 
     m_options = null;
 }
}
