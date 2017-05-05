// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import com.eegeo.tags.TagResources;
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

public class DepartmentSearchResultPoiView implements View.OnClickListener 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private TextView m_titleView = null;
    private TextView m_descriptionView = null;
    private ImageView m_tagIcon = null;
	private ImageView m_poiImage = null;
	private View m_poiImageProgressBar = null;
	private String m_poiImageUrl;

    public DepartmentSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_department_layout, m_uiRoot, false);
        RelativeLayout.LayoutParams layoutParams = (LayoutParams) m_view.getLayoutParams();
		if (m_activity.getResources().getBoolean(R.bool.isPhone)) {
			layoutParams.topMargin = layoutParams.bottomMargin = layoutParams.leftMargin = layoutParams.rightMargin = m_activity
					.dipAsPx(20);
		} else {
			layoutParams.topMargin = layoutParams.bottomMargin = m_activity.dipAsPx(40);
			layoutParams.leftMargin = layoutParams.rightMargin = (int) (m_uiRoot.getWidth() * 0.3f);
		}
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_descriptionView = (TextView)m_view.findViewById(R.id.search_result_poi_view_description);
        m_tagIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tag_icon);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_image);
        
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
    		final String title,
    		final String subtitle,
    		final String description,
    		final String primaryTag,
    		final String imageUrl)
    {
    	m_poiImageUrl = imageUrl;
    	
        m_titleView.setText(title);
        m_descriptionView.setText(description + subtitle);

        m_poiImage.setVisibility(View.GONE);
        m_poiImageProgressBar.setVisibility(View.GONE);

        if(!imageUrl.equals(""))
        {
        	m_poiImage.setVisibility(View.VISIBLE);
            m_poiImageProgressBar.setVisibility(View.VISIBLE);
        }
        
        int iconId = TagResources.getSmallIconForTag(m_activity, primaryTag);
        m_tagIcon.setImageResource(iconId);

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
				
			    int size = m_view.getWidth();
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
