// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.text.util.Linkify;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.categories.CategoryResources;

public class YelpSearchResultPoiView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_container = null;
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
    private	Button m_webVendorStyleLinkButton = null;
    private ImageView m_categoryIcon = null;
	private ImageView m_poiImage = null;
	private ImageView m_poiRatingImage = null;
	private View m_poiImageProgressBar = null;
	private String m_url;
	private String m_poiImageUrl;
	private String m_poiRatingUrl;

    public YelpSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_yelp_layout, m_uiRoot, false);

        final int boundsWidth = m_uiRoot.getWidth();
        final int boundsHeight = m_uiRoot.getHeight();
        final float boundsOccupyMultiplierHeight = 0.9f;
        final int mainWindowWidth = (int)Math.min(boundsWidth, 348.f);
        final int mainWindowHeight = (int)(boundsHeight * boundsOccupyMultiplierHeight);
        final int mainWindowX = (int)((boundsWidth * 0.5f) - (mainWindowWidth * 0.5f));
        final int mainWindowY = (int)((boundsHeight * 0.5f) - (mainWindowHeight * 0.5f));
        
        m_container = m_view.findViewById(R.id.search_result_poi_view_container);
        m_container.setX(mainWindowX);
        m_container.setY(mainWindowY);
        m_container.setLayoutParams(new RelativeLayout.LayoutParams(mainWindowWidth, mainWindowHeight));
        
        View scrollingContent = m_view.findViewById(R.id.search_result_poi_view_title_scrolling_content);
        final int availableScrollingContentHeight = mainWindowHeight - (m_activity.dipAsPx(30 + 55));
        scrollingContent.setLayoutParams(new LinearLayout.LayoutParams(mainWindowWidth, availableScrollingContentHeight));
        
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
        m_webVendorStyleLinkButton = (Button)m_view.findViewById(R.id.search_result_poi_view_web_vendor_link_style);
        m_webHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_web_header);
        m_categoryIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_category_icon);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_image);
		m_poiRatingImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_rating_image);
        m_vendorBranding = m_view.findViewById(R.id.search_result_poi_view_vendor_branding);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleCloseClicked();
			}
        });

        m_togglePinnedButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleTogglePinnedClicked();
			}
        });
        
        m_webVendorStyleLinkButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleWebLinkButtonClicked();
			}
		});
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
			    int scaleFactor = calculateInSampleSize(bmOptions, m_uiRoot.getWidth(), m_uiRoot.getHeight());
			    
			    bmOptions.inJustDecodeBounds = false;
			    bmOptions.inSampleSize = scaleFactor;
			    bmOptions.inPurgeable = true;
			    
			    Bitmap poiBitmap = BitmapFactory.decodeByteArray(imgData, 0, imgData.length, bmOptions);
			    m_poiImage.setImageBitmap(poiBitmap);
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
        SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
    }
    
    private void handleWebLinkButtonClicked()
    {
    	final Uri uri = Uri.parse(m_url);
    	final Intent browserIntent = new Intent(Intent.ACTION_VIEW, uri);
    	m_activity.startActivity(browserIntent);
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
