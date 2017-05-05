// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ProjectSwallowApp.R;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

public class PersonSearchResultPoiView implements View.OnClickListener 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private TextView m_nameView = null;
    private TextView m_jobTitleView = null;
    private TextView m_workingGroupView = null;
    private TextView m_locationView = null;
    private TextView m_deskView = null;
	private ImageView m_poiImage = null;
	private View m_poiImageProgressBar = null;
	
	private String m_poiImageUrl;

    public PersonSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_person_layout, m_uiRoot, false);
    	RelativeLayout.LayoutParams layoutParams = (LayoutParams) m_view.getLayoutParams();
		if (m_activity.getResources().getBoolean(R.bool.isPhone)) {
			layoutParams.topMargin = layoutParams.bottomMargin = layoutParams.leftMargin = layoutParams.rightMargin = m_activity
					.dipAsPx(20);
		} else {
			layoutParams.topMargin = layoutParams.bottomMargin = m_activity.dipAsPx(40);
			layoutParams.leftMargin = layoutParams.rightMargin = (int) (m_uiRoot.getWidth() * 0.3f);
		}
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_nameView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_jobTitleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_job_title);
        m_workingGroupView = (TextView)m_view.findViewById(R.id.search_result_poi_view_working_group);
        m_locationView = (TextView)m_view.findViewById(R.id.search_result_poi_view_location);
        m_deskView = (TextView)m_view.findViewById(R.id.search_result_poi_view_desk);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_primary_tag_icon);
        
        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(this);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayPoiInfo(
    		final String name,
    		final String jobTitle,
    		final String workingGroup, 
    		final String location,
    		final String deskCode,
    		final String imageUrl)
    {
        m_nameView.setText(name);
        m_poiImageUrl = imageUrl;
        
        if(!jobTitle.equals(""))
        {
            m_jobTitleView.setVisibility(View.VISIBLE);
            m_jobTitleView.setText("Job Title: " + jobTitle);
        }
        else
        {
        	m_jobTitleView.setVisibility(View.GONE);
        }

        if(!workingGroup.equals(""))
        {
            m_workingGroupView.setVisibility(View.VISIBLE);
            m_workingGroupView.setText("Working Group: " + workingGroup);
        }
        else
        {
        	m_workingGroupView.setVisibility(View.GONE);
        }

        if(!location.equals(""))
        {
            m_locationView.setVisibility(View.VISIBLE);
            m_locationView.setText("Location: " + location);
        }
        else
        {
        	m_locationView.setVisibility(View.GONE);
        }

        if(!deskCode.equals(""))
        {
            m_deskView.setVisibility(View.VISIBLE);
            m_deskView.setText("Desk: " + deskCode);
        }
        else
        {
        	m_deskView.setVisibility(View.GONE);
        }
        
        m_poiImage.setVisibility(View.INVISIBLE);
        
        m_closeButton.setEnabled(true);
    	
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
    }

    public void onClick(View view)
    {
        if(view == m_closeButton)
        {
			handleCloseClicked();
        }
    }

    public void dismissPoiInfo()
    {
        m_view.setVisibility(View.GONE);
    }

	public void updateImageData(String url, boolean hasImage, final byte[] imgData)
	{
		if(url.equals(m_poiImageUrl))
		{
			m_poiImageProgressBar.setVisibility(View.GONE);
			
			if(hasImage)
			{
				m_poiImage.setVisibility(View.VISIBLE);
				
			    BitmapFactory.Options bmOptions = new BitmapFactory.Options();
			    bmOptions.inJustDecodeBounds = true;
			    bmOptions.inJustDecodeBounds = false;
			    bmOptions.inPurgeable = true;
				
				int size = m_activity.dipAsPx(280);
				Bitmap poiBitmap = BitmapFactory.decodeByteArray(imgData, 0, imgData.length, bmOptions);
				m_poiImage.setImageBitmap(Bitmap.createScaledBitmap(poiBitmap, size, size, false));
			}
		}
	}

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);

        SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }
    
    
	public static int calculateInSampleSize(BitmapFactory.Options options, int reqWidth, int reqHeight)
	{
	    // Raw height and width of image
	    final int height = options.outHeight;
	    final int width = options.outWidth;
	    int inSampleSize = 1;
	    
	    if (height > reqHeight || width > reqWidth)
	    {	
	        final int halfHeight = height / 2;
	        final int halfWidth = width / 2;
	        
	        // Calculate the largest inSampleSize value that is a power of 2 and keeps both
	        // height and width larger than the requested height and width.
	        while ((halfHeight / inSampleSize) > reqHeight && (halfWidth / inSampleSize) > reqWidth) 
	        {
	            inSampleSize *= 2;
	        }
	    }
	    
	    return inSampleSize;
	}
}
