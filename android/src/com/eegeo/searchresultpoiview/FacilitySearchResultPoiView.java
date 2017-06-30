// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.tags.TagResources;
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

public class FacilitySearchResultPoiView implements View.OnClickListener 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private TextView m_titleView = null;
    private View m_descriptionDivider = null;
    private ImageView m_descriptionIcon = null;
    private TextView m_descriptionView = null;
    private View m_categoriesDivider = null;
    private ImageView m_categoriesIcon = null;
    private TextView m_categoriesView = null;
    private ImageView m_tagIcon = null;
	private ImageView m_poiImage = null;
	private View m_poiImageProgressBar = null;
	private String m_poiImageUrl;

    public FacilitySearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_facility_layout, m_uiRoot, false);
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
        m_descriptionDivider = m_view.findViewById(R.id.search_result_poi_view_description_divider);
        m_descriptionIcon = (ImageView) m_view.findViewById(R.id.search_result_poi_view_description_icon);
        m_descriptionView = (TextView)m_view.findViewById(R.id.search_result_poi_view_description);
        m_categoriesDivider = m_view.findViewById(R.id.search_result_poi_view_categories_divider);
        m_categoriesIcon = (ImageView) m_view.findViewById(R.id.search_result_poi_view_categories_icon);
        m_categoriesView = (TextView) m_view.findViewById(R.id.search_result_poi_view_categories);
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
    		final String description,
    		final String primaryTag,
            final String[] humanReadableTags,
    		final String imageUrl)
    {
    	m_poiImageUrl = imageUrl;
    	
        m_titleView.setText(title);
        m_descriptionView.setText(description);

        m_descriptionDivider.setVisibility(View.GONE);
        m_descriptionIcon.setVisibility(View.GONE);
        m_descriptionView.setVisibility(View.GONE);

        if(!description.equals(""))
        {
            m_descriptionDivider.setVisibility(View.VISIBLE);
            m_descriptionIcon.setVisibility(View.VISIBLE);
            m_descriptionView.setVisibility(View.VISIBLE);
        }

        m_categoriesDivider.setVisibility(View.GONE);
        m_categoriesIcon.setVisibility(View.GONE);
        m_categoriesView.setVisibility(View.GONE);

        if(humanReadableTags.length > 0)
        {
            m_categoriesDivider.setVisibility(View.VISIBLE);
            m_categoriesIcon.setVisibility(View.VISIBLE);
            m_categoriesView.setVisibility(View.VISIBLE);

            String output = new String();
            output += humanReadableTags[0];
            for(int i = 1; i < humanReadableTags.length; ++ i)
            {
                output += (", " + humanReadableTags[i]);
            }
            m_categoriesView.setText(output);
        }

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
				
				int size = m_uiRoot.getWidth();
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
