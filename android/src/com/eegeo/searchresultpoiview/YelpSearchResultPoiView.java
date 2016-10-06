// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.TintablePinToggleButton;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.tags.TagResources;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.text.util.Linkify;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class YelpSearchResultPoiView implements View.OnClickListener 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private View m_togglePinnedButton = null;
    private TextView m_titleView = null;
    private TextView m_addressView = null;
    private TextView m_addressHeader = null;
    private TextView m_phoneView = null;
    private TextView m_phoneHeader = null;
    private TextView m_humanReadableTagsView = null;
    private TextView m_humanReadableTagsHeader = null;
    private TextView m_reviewsView = null;
    private TextView m_reviewsHeader = null;
    private	ImageView m_webVendorStyleLinkButton = null;
    private ImageView m_tagIcon = null;
	private ImageView m_poiImage = null;
	private ImageView m_poiRatingImage = null;
	private ImageView m_poiRatingOverImage = null;
	private View m_poiImageProgressBar = null;
	private RelativeLayout m_poiRatingOverImageContainer = null;
	private TextView m_poiRatingOverImageReviewCount = null;
	private TextView m_poiRatingReviewCount = null;
	private View m_poiImageGradient = null;
	private String m_url;
	private String m_poiImageUrl;

    private boolean m_handlingClick = false;
    private TintablePinToggleButton m_togglePinnedWrapper;

    public YelpSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_yelp_layout, m_uiRoot, false);

        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_togglePinnedButton = m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
        m_togglePinnedWrapper = new TintablePinToggleButton(m_togglePinnedButton);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_addressView = (TextView)m_view.findViewById(R.id.search_result_poi_view_address);
        m_addressHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_address_header);
        m_phoneView = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone);
        m_phoneHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone_header);
        m_humanReadableTagsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_tags);
        m_humanReadableTagsHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_tags_header);
        m_reviewsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_reviews);
        m_reviewsHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_reviews_header);
        m_webVendorStyleLinkButton = (ImageView)m_view.findViewById(R.id.search_result_poi_view_web_vendor_link_style);
        m_tagIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tag_icon);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_image);
		m_poiRatingImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_rating_image);
		m_poiRatingOverImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_rating_over_image);
		m_poiRatingOverImageContainer = (RelativeLayout)m_view.findViewById(R.id.search_result_poi_view_rating_over_image_container);
		m_poiRatingOverImageReviewCount = (TextView)m_view.findViewById(R.id.search_result_poi_view_rating_over_image_review_count);
		m_poiRatingReviewCount = (TextView)m_view.findViewById(R.id.search_result_poi_view_rating_review_count);
		m_poiImageGradient = m_view.findViewById(R.id.search_result_poi_view_image_gradient);
		
        
        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_poiRatingImage.setVisibility(View.GONE);
        m_poiRatingOverImage.setVisibility(View.GONE);
        
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
    		final String iconKey,
    		final String[] humanReadableTags,
    		final String imageUrl,
    		final String ratingImageUrl,
    		final String vendor,
    		final String[] reviews,
    		final int reviewCount,
    		final boolean isPinned)
    {
    	m_url = url;
    	m_poiImageUrl = imageUrl;
    	
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
            m_webVendorStyleLinkButton.setVisibility(View.VISIBLE);
        }
        else
        {
        	m_webVendorStyleLinkButton.setVisibility(View.GONE);
        }

        if(humanReadableTags.length > 0)
        {
        	m_humanReadableTagsHeader.setVisibility(View.VISIBLE);
        	m_humanReadableTagsView.setVisibility(View.VISIBLE);
        	
        	String output = new String();
        	output += humanReadableTags[0]; 
        	for(int i = 1; i < humanReadableTags.length; ++ i)
        	{
        		output += ("\n" + humanReadableTags[i]);
        	}
        	m_humanReadableTagsView.setText(output);
        }
        else
        {
        	m_humanReadableTagsHeader.setVisibility(View.GONE);
            m_humanReadableTagsView.setVisibility(View.GONE);
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
        
        //m_vendorBranding.setVisibility(View.VISIBLE);
        m_poiImage.setVisibility(View.GONE);
        m_poiImageProgressBar.setVisibility(View.GONE);
        m_poiRatingImage.setVisibility(View.GONE);
        m_poiRatingOverImageContainer.setVisibility(View.GONE);
    	m_poiRatingReviewCount.setVisibility(View.GONE);
    	m_poiImageGradient.setVisibility(View.GONE);

        if(!imageUrl.equals(""))
        {
            m_poiImageProgressBar.setVisibility(View.VISIBLE);
        }
        
        m_poiRatingImage.setVisibility(View.GONE);
        m_poiRatingOverImage.setVisibility(View.GONE);
        if (!ratingImageUrl.equals("") && reviewCount > 0)
        {
        	int imageResource = m_activity.getResources().getIdentifier(ratingImageUrl, "drawable", m_activity.getPackageName());
            Drawable image = m_activity.getResources().getDrawable(imageResource);
            
            if(imageUrl.equals(""))
            {
            	m_poiRatingImage.setImageDrawable(image);
    		    m_poiRatingImage.setVisibility(View.VISIBLE);
            	m_poiRatingReviewCount.setVisibility(View.VISIBLE);
            	m_poiRatingReviewCount.setText("(" + reviewCount + ")");
            }
            else
            {
            	m_poiRatingOverImageContainer.setVisibility(View.VISIBLE);
            	m_poiRatingOverImage.setImageDrawable(image);
            	m_poiRatingOverImage.setVisibility(View.VISIBLE);
            	m_poiRatingOverImageReviewCount.setVisibility(View.VISIBLE);
            	m_poiRatingOverImageReviewCount.setText("(" + reviewCount + ")");
            	m_poiImageGradient.setVisibility(View.VISIBLE);
            }   
        }
        
        int iconId = TagResources.getSmallIconForTag(m_activity, iconKey);
        m_tagIcon.setImageResource(iconId);

        m_closeButton.setEnabled(true);
        m_togglePinnedWrapper.setPinToggleState(isPinned);
    	
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
	}

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);
        m_togglePinnedButton.setOnClickListener(null);

        SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }
    
    private void handleWebLinkButtonClicked()
    {
    	final Uri uri = Uri.parse(m_url);
    	final Intent browserIntent = new Intent(Intent.ACTION_VIEW, uri);
    	if(browserIntent.resolveActivity(m_activity.getPackageManager()) != null)
    	{
    		m_activity.startActivity(browserIntent);
    	}
    	else
    	{
    		new AlertDialog.Builder(m_activity)
    			.setTitle("Warning")
    			.setMessage("No web browser found on device. Cannot open webpage.")
    			.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) 
					{
					}
				})
    			.show();
    	}
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

    private void handleTogglePinnedClicked()
    {
    	if(m_togglePinnedWrapper.isPinned())
    	{
    		showRemovePinDialog();
    	}
    	else
    	{
    		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
            m_handlingClick = false;
            m_togglePinnedWrapper.setPinToggleState(true);
    	}
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
                m_togglePinnedWrapper.setPinToggleState(false);
            }
        })
        .setNegativeButton("No,  keep it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
            	m_togglePinnedWrapper.setPinToggleState(true);
                m_handlingClick = false;
            }
        })
        .setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            @Override
            public void onCancel(DialogInterface dialog)
            {
            	m_togglePinnedWrapper.setPinToggleState(true);
                m_handlingClick = false;
            }
        });
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
