// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.text.util.Linkify;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.categories.CategoryResources;

public class YelpSearchResultPoiView implements View.OnClickListener 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private ToggleButton m_togglePinnedButton = null;
    private View m_vendorBranding = null;
    private TextView m_titleView = null;
    private TextView m_addressView = null;
    private TextView m_addressHeader = null;
    private TextView m_phoneView = null;
    private TextView m_phoneHeader = null;
    private TextView m_humanReadableCategoriesView = null;
    private TextView m_humanReadableCategoriesHeader = null;
    private TextView m_reviewsView = null;
    private TextView m_reviewsHeader = null;
    private	TextView m_webHeader = null;
    private	ImageButton m_webVendorStyleLinkButton = null;
    private ImageView m_categoryIcon = null;
	private ImageView m_poiImage = null;
	private ImageView m_poiRatingImage = null;
	private View m_poiImageProgressBar = null;
	private String m_url;
	private String m_poiImageUrl;
	private String m_poiRatingUrl;

    private boolean m_handlingClick = false;

    public YelpSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_yelp_layout, m_uiRoot, false);

        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_togglePinnedButton = (ToggleButton)m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_addressView = (TextView)m_view.findViewById(R.id.search_result_poi_view_address);
        m_addressHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_address_header);
        m_phoneView = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone);
        m_phoneHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone_header);
        m_humanReadableCategoriesView = (TextView)m_view.findViewById(R.id.search_result_poi_view_categories);
        m_humanReadableCategoriesHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_categories_header);
        m_reviewsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_reviews);
        m_reviewsHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_reviews_header);
        m_webVendorStyleLinkButton = (ImageButton)m_view.findViewById(R.id.search_result_poi_view_web_vendor_link_style);
        m_webHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_web_header);
        m_categoryIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_category_icon);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_image);
		m_poiRatingImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_rating_image);
        m_vendorBranding = m_view.findViewById(R.id.search_result_poi_view_vendor_branding);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(this);
        m_togglePinnedButton.setOnClickListener(this);
        m_webVendorStyleLinkButton.setOnClickListener(this);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayPoiInfo(
    		final String title,
    		final String address,
    		final String phone, 
    		final String url,
    		final String category,
    		final String[] humanReadableCategories,
    		final String imageUrl,
    		final String ratingImageUrl,
    		final String vendor,
    		final String[] reviews,
    		final boolean isPinned)
    {
    	m_url = url;
    	m_poiImageUrl = imageUrl;
    	m_poiRatingUrl = ratingImageUrl;
    	
        m_titleView.setText(title);

        if(!address.equals(""))
        {
            m_addressHeader.setVisibility(View.VISIBLE);
            m_addressView.setVisibility(View.VISIBLE);
            String addressText = address.replace(", ", "\n");
            m_addressView.setText(addressText);
            m_addressHeader.setText(vendor.equals("GeoNames") ? "Country" : "Address");
        }
        else
        {
            m_addressHeader.setVisibility(View.GONE);
            m_addressView.setVisibility(View.GONE);
        }

        if(!phone.equals(""))
        {
            m_phoneHeader.setVisibility(View.VISIBLE);
            m_phoneView.setVisibility(View.VISIBLE);
            m_phoneView.setText(phone.replace(" ", ""));

            // Autolink discards country code so add custom phone link
            final String phoneRegex = "[\\S]*";
            Linkify.addLinks(m_phoneView, Pattern.compile(phoneRegex), "Tel:");
        }
        else
        {
            m_phoneHeader.setVisibility(View.GONE);
            m_phoneView.setVisibility(View.GONE);
        }

        if(!url.equals(""))
        {
            m_webHeader.setVisibility(View.VISIBLE);
            m_webVendorStyleLinkButton.setVisibility(View.VISIBLE);
        }
        else
        {
            m_webHeader.setVisibility(View.GONE);
        	m_webVendorStyleLinkButton.setVisibility(View.GONE);
        }

        if(humanReadableCategories.length > 0)
        {
        	m_humanReadableCategoriesHeader.setVisibility(View.VISIBLE);
        	m_humanReadableCategoriesView.setVisibility(View.VISIBLE);
        	
        	String output = new String();
        	output += humanReadableCategories[0]; 
        	for(int i = 1; i < humanReadableCategories.length; ++ i)
        	{
        		output += ("\n" + humanReadableCategories[i]);
        	}
        	m_humanReadableCategoriesView.setText(output);
        }
        else
        {
        	m_humanReadableCategoriesHeader.setVisibility(View.GONE);
            m_humanReadableCategoriesView.setVisibility(View.GONE);
        }

        if(reviews.length > 0)
        {
        	m_reviewsHeader.setVisibility(View.VISIBLE);
        	m_reviewsView.setVisibility(View.VISIBLE);
        	m_reviewsView.setText(reviews[0]);
        }
        else
        {
        	m_reviewsHeader.setVisibility(View.GONE);
        	m_reviewsView.setVisibility(View.GONE);
        }
        
        m_vendorBranding.setVisibility(View.VISIBLE);
        m_poiImage.setVisibility(View.GONE);
        m_poiImageProgressBar.setVisibility(View.GONE);
        m_poiRatingImage.setVisibility(View.GONE);

        if(!imageUrl.equals(""))
        {
            m_poiImageProgressBar.setVisibility(View.VISIBLE);
        }
        
        int iconId = CategoryResources.getSmallIconForCategory(m_activity, category);
        m_categoryIcon.setImageResource(iconId);

        m_closeButton.setEnabled(true);
    	m_togglePinnedButton.setChecked(isPinned);
    	
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();

        m_handlingClick = false;
    }

    public void onClick(View view)
    {
        if(m_handlingClick)
        {
            return;
        }
        m_handlingClick = true;

        if(view == m_closeButton)
        {
			handleCloseClicked();
        }
        else if(view == m_togglePinnedButton)
        {
			handleTogglePinnedClicked();
        }
        else if(view == m_webVendorStyleLinkButton) 
        {
			handleWebLinkButtonClicked();
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
		else if(url.equals(m_poiRatingUrl))
		{
			if(hasImage)
			{
				m_poiRatingImage.setVisibility(View.VISIBLE);
				
			    BitmapFactory.Options bmOptions = new BitmapFactory.Options();
			    bmOptions.inJustDecodeBounds = true;
			    int scaleFactor = calculateInSampleSize(bmOptions, m_uiRoot.getWidth(), m_uiRoot.getHeight());
			    
			    bmOptions.inJustDecodeBounds = false;
			    bmOptions.inSampleSize = scaleFactor;
			    bmOptions.inPurgeable = true;
			    
			    Bitmap poiBitmap = BitmapFactory.decodeByteArray(imgData, 0, imgData.length, bmOptions);
			    m_poiRatingImage.setImageBitmap(poiBitmap);
			}
		}
	}

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);
        m_togglePinnedButton.setOnClickListener(null);

        SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    private void handleTogglePinnedClicked()
    {
    	// Undo the toggle which occurred on this click, we will redo it manually if confirmed.
    	m_togglePinnedButton.setChecked(!m_togglePinnedButton.isChecked());
		
    	if(m_togglePinnedButton.isChecked())
    	{
    		showRemovePinDialog();
    	}
    	else
    	{
    		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
            m_handlingClick = false;
            m_togglePinnedButton.setChecked(true);
    	}
    }
    
    private void handleWebLinkButtonClicked()
    {
    	final Uri uri = Uri.parse(m_url);
    	final Intent browserIntent = new Intent(Intent.ACTION_VIEW, uri);
    	m_activity.startActivity(browserIntent);
        m_handlingClick = false;
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
	
	private void showRemovePinDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle("Remove Pin")
        .setMessage("Are you sure you want to remove this pin?")
        .setPositiveButton("Yes,  delete it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int id)
            {
        		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
                m_handlingClick = false;
                m_togglePinnedButton.setChecked(false);
            }
        })
        .setNegativeButton("No,  keep it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
            	m_togglePinnedButton.setChecked(true);
                m_handlingClick = false;
            }
        })
        .setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            @Override
            public void onCancel(DialogInterface dialog)
            {
            	m_togglePinnedButton.setChecked(true);
                m_handlingClick = false;
            }
        });
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
