// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import android.annotation.SuppressLint;
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
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.helpers.TintablePinToggleButton;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.tags.TagResources;

public class YelpSearchResultPoiView implements View.OnClickListener, IBackButtonListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private View m_togglePinnedButton = null;
    private TextView m_titleView = null;
    private TextView m_addressView = null;
    private TextView m_phoneView = null;
    private TextView m_humanReadableTagsView = null;
    private TextView m_reviewsView = null;
    private	ImageView m_webVendorStyleLinkButton = null;
    private ImageView m_tagIcon = null;
	private ImageView m_poiImage = null;
	private ImageView m_poiRatingImage = null;
	private ImageView m_poiRatingOverImage = null;
	private View m_poiImageViewContainer = null;
	private View m_poiImageProgressBar = null;
	private RelativeLayout m_poiRatingOverImageContainer = null;
	private TextView m_poiRatingOverImageReviewCount = null;
	private TextView m_poiRatingReviewCount = null;
	private View m_poiImageGradient = null;
	private String m_url;
	private String m_poiImageUrl;
	private ImageView m_addressIcon = null;
	private ImageView m_phoneIcon = null;
	private ImageView m_tagsIcon = null;
	private ImageView m_review_icon = null;
	private View m_detailsHeader = null;
	private View m_humanReadableTagsHeader = null;
	private View m_poiImageHeader = null;
	private ScrollView m_contentContainer = null;
	private ImageView m_footerFade = null;
	private LinearLayout m_linearContentContainer = null;
	private TextView m_dropPinText = null;

    private boolean m_handlingClick = false;
    private TintablePinToggleButton m_togglePinnedWrapper;
    
    private static String m_pinTextDefault = "Drop Pin";
    private static String m_pinTextPressed = "Remove Pin";

    @SuppressLint("NewApi")
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
        m_phoneView = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone);
        m_humanReadableTagsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_tags);
        m_reviewsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_reviews);
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
		m_poiImageViewContainer = (View)m_view.findViewById(R.id.search_result_poi_view_image_container);
		m_addressIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_address_icon);
		m_phoneIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_phone_icon);
		m_tagsIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tags_icon);
		m_review_icon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_reviews_icon);
		m_detailsHeader = (View)m_view.findViewById(R.id.search_result_poi_view_details_header);
		m_humanReadableTagsHeader = (View)m_view.findViewById(R.id.search_result_poi_view_tags_header);
		m_poiImageHeader = (View)m_view.findViewById(R.id.search_result_poi_image_header);
		m_contentContainer = (ScrollView)m_view.findViewById(R.id.content_container);
		m_footerFade = (ImageView)m_view.findViewById(R.id.footer_fade);
		m_linearContentContainer = (LinearLayout)m_view.findViewById(R.id.linear_content_container);
		m_dropPinText = (TextView)m_view.findViewById(R.id.drop_pin_text);
        
        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_poiRatingImage.setVisibility(View.GONE);
        m_poiRatingOverImage.setVisibility(View.GONE);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(this);
        m_togglePinnedButton.setOnClickListener(this);
        m_webVendorStyleLinkButton.setOnClickListener(this);
        m_activity.addBackButtonPressedListener(this);
    }

    public void destroy()
    {
        m_activity.removeBackButtonPressedListener(this);
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
        
        if(!address.equals("") || !phone.equals(""))
        {
            m_detailsHeader.setVisibility(View.VISIBLE);
        }
        else
        {
            m_detailsHeader.setVisibility(View.GONE);
        }

        if(!address.equals(""))
        {
            m_addressView.setVisibility(View.VISIBLE);
            m_addressIcon.setVisibility(View.VISIBLE);
            String addressText = address.replace(", ", "\n");
            m_addressView.setText(addressText);
        }
        else
        {
            m_addressView.setVisibility(View.GONE);
            m_addressIcon.setVisibility(View.GONE);
        }

        if(!phone.equals(""))
        {
            m_phoneView.setVisibility(View.VISIBLE);
            m_phoneIcon.setVisibility(View.VISIBLE);
            m_phoneView.setText(phone.replace(" ", ""));

            // Autolink discards country code so add custom phone link
            final String phoneRegex = "[\\S]*";
            Linkify.addLinks(m_phoneView, Pattern.compile(phoneRegex), "Tel:");
        }
        else
        {
            m_phoneView.setVisibility(View.GONE);
            m_phoneIcon.setVisibility(View.GONE);
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
        	m_humanReadableTagsView.setVisibility(View.VISIBLE);
        	m_humanReadableTagsHeader.setVisibility(View.VISIBLE);
        	m_tagsIcon.setVisibility(View.VISIBLE);
        	
        	String output = new String();
        	output += humanReadableTags[0]; 
        	for(int i = 1; i < humanReadableTags.length; ++ i)
        	{
        		output += (", " + humanReadableTags[i]);
        	}
        	m_humanReadableTagsView.setText(output);
        }
        else
        {
            m_humanReadableTagsView.setVisibility(View.GONE);
            m_humanReadableTagsHeader.setVisibility(View.GONE);
            m_tagsIcon.setVisibility(View.GONE);
        }

        if(reviews.length > 0)
        {
        	m_reviewsView.setVisibility(View.VISIBLE);
        	m_review_icon.setVisibility(View.VISIBLE);
        	m_reviewsView.setText(reviews[0]);
        }
        else
        {
        	m_reviewsView.setVisibility(View.GONE);
        	m_review_icon.setVisibility(View.GONE);
        }
        
        m_poiImageProgressBar.setVisibility(View.GONE);
        m_poiRatingImage.setVisibility(View.GONE);
        m_poiRatingOverImageContainer.setVisibility(View.GONE);
    	m_poiRatingReviewCount.setVisibility(View.GONE);
    	m_poiImageGradient.setVisibility(View.GONE);

        if(!imageUrl.equals(""))
        {
            m_poiImageProgressBar.setVisibility(View.VISIBLE);
            m_poiImageViewContainer.setVisibility(View.VISIBLE);
        }
        else
        {
        	m_poiImageViewContainer.setVisibility(View.GONE);
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
        
        if(m_togglePinnedWrapper.isPinned())
        {
        	m_dropPinText.setText("Remove Pin");
        }
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
    
    public void HandleFooterFadeInitialVisibility()
    {
        int childHeight = m_linearContentContainer.getHeight();
        boolean isScrollable = m_contentContainer.getHeight() < (childHeight + m_contentContainer.getPaddingTop() + m_contentContainer.getPaddingBottom());
        if(!isScrollable)
        {
        	m_footerFade.setVisibility(View.GONE);
        }
        else
        {
        	m_footerFade.setVisibility(View.VISIBLE);
        }
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
				
			    m_poiImage.getLayoutParams().height = (int) (m_poiImage.getWidth() * 2.f / 3.f);
				int width = m_activity.dipAsPx(m_poiImage.getWidth());
				int height = (int) (width * 2.f / 3.f);
				Bitmap poiBitmap = BitmapFactory.decodeByteArray(imgData, 0, imgData.length, bmOptions);
				m_poiImage.setImageBitmap(Bitmap.createBitmap(poiBitmap));
			}
		}
		
		HandleFooterFadeInitialVisibility();
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
            m_dropPinText.setText(m_pinTextPressed);
    	}
    }
	
	private void showRemovePinDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle(m_pinTextPressed)
        .setMessage("Are you sure you want to remove this pin?")
        .setPositiveButton("Yes,  delete it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int id)
            {
        		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
                m_handlingClick = false;
                m_togglePinnedWrapper.setPinToggleState(false);
                m_dropPinText.setText(m_pinTextDefault);
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

    @Override
    public boolean onBackButtonPressed() {
        if (m_view.getVisibility() == View.VISIBLE)
        {
            handleCloseClicked();
            return true;
        }
        return false;
    }
}
