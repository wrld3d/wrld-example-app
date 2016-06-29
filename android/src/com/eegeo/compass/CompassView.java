// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.compass;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IRuntimePermissionResultHandler;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.runtimepermissions.RuntimePermissionDispatcher;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v4.app.ActivityCompat;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;

public class CompassView implements View.OnClickListener, IRuntimePermissionResultHandler
{
    private MainActivity m_activity = null;
    private long m_nativeCallerPointer;
    private View m_view = null;
    private View m_compassPoint = null;
    private ImageView m_compassInner = null;

    private float m_yPosActive;
    private float m_yPosInactive;
    private float m_compassPointOffsetX;
    private float m_compassPointOffsetY;
    
    private final long m_stateChangeAnimationTimeMilliseconds = 200;

    public CompassView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        createView();
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_view);
        m_view = null;
        m_activity.getRuntimePermissionDispatcher().removeIRuntimePermissionResultHandler(this);
    }

    private void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.compass_layout, uiRoot, false);
        m_view.setOnClickListener(this);

        m_compassPoint = m_view.findViewById(R.id.compass_arrow_shape);
        m_compassInner = (ImageView)m_view.findViewById(R.id.compass_inner_shape);
    	m_compassInner.setVisibility(View.GONE);
    	
    	m_activity.getRuntimePermissionDispatcher().addRuntimePermissionResultHandler(this);

        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{   
		        final float screenWidth = uiRoot.getWidth();
		        final float screenHeight = uiRoot.getHeight();
		        final float viewWidth = m_view.getWidth();
		        final float viewHeight = m_view.getHeight();
		        final float pointWidth = m_compassPoint.getWidth();
		        final float pointHeight = m_compassPoint.getHeight();

		    	m_compassPointOffsetX = (viewWidth * 0.5f) - (pointWidth * 0.5f);
		        m_compassPointOffsetY = (viewHeight * 0.5f) - (pointHeight * 0.5f);
		        
		        m_yPosActive = (screenHeight - viewWidth) - m_activity.dipAsPx(8.f);
		        m_yPosInactive = screenHeight + viewHeight;
		        
		        m_view.setX((screenWidth * 0.5f) - (viewWidth * 0.5f));
		        m_view.setY(m_yPosInactive);
		        m_view.removeOnLayoutChangeListener(this);
			}
        });

        uiRoot.addView(m_view);
        showGpsDisabledView();
    }

    public void updateHeading(float headingAngleRadians)
    {
    	final float verticalPointOffsetPx = 25.f;
       	final float theta = -headingAngleRadians;
       	final float sinTheta = (float)Math.sin(theta);
        final float cosTheta = (float)Math.cos(theta);
        final float x = 0.f;
        final float y = m_activity.dipAsPx(-verticalPointOffsetPx);
        final float newX = x*cosTheta - y*sinTheta;
        final float newY = y*cosTheta + x*sinTheta;
        m_compassPoint.setX(m_compassPointOffsetX + newX);
        m_compassPoint.setY(m_compassPointOffsetY + newY);
    	m_compassPoint.setRotation((float) -Math.toDegrees(headingAngleRadians));
    }

    public void showGpsDisabledView()
    { 
    	m_compassInner.setVisibility(View.GONE);
    }

    public void showGpsFollowView()
    {  
    	m_compassInner.setVisibility(View.VISIBLE);
    	createBitMap(Paint.Style.STROKE);
    }

    public void showGpsCompassModeView()
    { 
    	m_compassInner.setVisibility(View.VISIBLE);
    	createBitMap(Paint.Style.FILL);
    }
    
    public void notifyGpsUnauthorized()
    {
    	AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(m_activity);
    	alertDialogBuilder.setTitle("Location Services disabled")
    		.setMessage("GPS Compass inaccessable: Location Services are not enabled for this application. You can change this in your device settings.")
    		.setCancelable(false)
    		.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
				}
			});
    	AlertDialog alert = alertDialogBuilder.create();
    	alert.show();
    }

    @Override
    public void onClick(View view)
    {
    	if(m_activity.getRuntimePermissionDispatcher().hasLocationPermissions())
    	{
    		CompassViewJniMethods.HandleClick(m_nativeCallerPointer);
    	}
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
    
    private void createBitMap(Paint.Style style) 
    {
        final int innerDiameter = m_activity.dipAsPx(20);
        Bitmap bmp = Bitmap.createBitmap(innerDiameter, innerDiameter, Bitmap.Config.ARGB_8888);
        Canvas compassInnerCanvas = new Canvas(bmp);
        compassInnerCanvas.drawColor(Color.TRANSPARENT);
        Paint compassInnerPaint = new Paint();
        compassInnerPaint.setStyle(style);
        compassInnerPaint.setColor(m_activity.getResources().getColor(R.color.white));
        compassInnerPaint.setAntiAlias(true);
        compassInnerPaint.setFilterBitmap(true);
        compassInnerCanvas.drawCircle(innerDiameter / 2, innerDiameter/2 , innerDiameter/2, compassInnerPaint);   
        m_compassInner.setImageBitmap(bmp);  
        m_compassInner.invalidate();
    }
    
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) 
    {
        if (requestCode != RuntimePermissionDispatcher.GPS_PERMISSION_REQUEST_CODE)
            return;
		// If request is cancelled, the result arrays are empty.
		if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) 
		{
			CompassViewJniMethods.HandleClick(m_nativeCallerPointer);
		}
		else
		{
			// If any of the permission is denied, we can't use the camera
			// properly, so we will show the dialog with agree or cancel dialog
			showPermissionRequiredDialog(m_activity);
		}
		return;
	}
    
    private void showPermissionRequiredDialog(final Activity context) 
    {
		DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener()
		{
			@Override
			public void onClick(DialogInterface dialog, int which) 
			{
				dialog.dismiss();
				switch (which)
				{
				case DialogInterface.BUTTON_POSITIVE:
					if(ActivityCompat.shouldShowRequestPermissionRationale(context, Manifest.permission.ACCESS_FINE_LOCATION))
					{
						// Checking Permissions again
						m_activity.getRuntimePermissionDispatcher().hasLocationPermissions();
					}
					else
					{
						// Open App's Settings Page for user to grand permission manually
						m_activity.getRuntimePermissionDispatcher().startAppSettings(context);
					}
					break;
				}
			}
		};

		AlertDialog.Builder builder = new AlertDialog.Builder(context);
		builder.setMessage(context.getResources().getString(R.string.required_location_permission_text))
				.setPositiveButton(context.getResources().getString(R.string.ok_text), dialogClickListener)
				.setNegativeButton(context.getResources().getString(R.string.cancel_text), dialogClickListener).show();
	}
}
