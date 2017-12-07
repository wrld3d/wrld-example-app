// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.text.util.Linkify;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.webkit.WebViewClient;
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

public class EegeoSearchResultPoiView implements View.OnClickListener, IBackButtonListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    
    private View m_searchResultPoiViewContainer = null;
    private View m_closeButton = null;
    private View m_togglePinnedButton = null;
    private TextView m_titleView = null;
    private TextView m_subtitleView = null;
    private TextView m_addressView = null;
    private View m_detailsHeader = null;
    private TextView m_phoneView = null;
    private TextView m_webLinkView = null;
    private TextView m_humanReadableTagsView = null;
    private View m_humanReadableTagsHeader = null;
    private ImageView m_tagIcon = null;
    private TextView m_descriptionView = null;
    private View m_poiImageHeader = null;
	private ImageView m_poiImage = null;
	private View m_poiImageProgressBar = null;
	private View m_poiImageGradient = null;
	private String m_url = null;
	private String m_poiImageUrl = null;
	private ImageView m_facebookUrl = null;
	private ImageView m_twitterUrl = null;
	private ImageView m_email = null;
	private ImageView m_addressIcon = null;
	private ImageView m_phoneIcon = null;
	private ImageView m_webIcon = null;
	private ImageView m_tagsIcon = null;
	private ImageView m_descriptionIcon = null;
	private View m_poiImageViewContainer = null;
	private TextView m_dropPinText = null;
	private ScrollView m_contentContainer = null;
	private ImageView m_footerFade = null;
	private LinearLayout m_linearContentContainer = null;
	private WebView m_webView = null;
	private View m_webViewContainer = null;
	
	private boolean m_htmlLoaded = true;
    private boolean m_handlingClick = false;
    private TintablePinToggleButton m_togglePinnedWrapper;
    
    private static String m_pinTextDefault = "Drop Pin";
    private static String m_pinTextPressed = "Remove Pin";

    @SuppressLint("NewApi")
	public EegeoSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_eegeo_layout, m_uiRoot, false);
       
        m_searchResultPoiViewContainer = m_view.findViewById(R.id.search_result_poi_view_container);
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_togglePinnedButton = m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
        m_togglePinnedWrapper = new TintablePinToggleButton(m_togglePinnedButton);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_subtitleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_subtitle);
        m_addressView = (TextView)m_view.findViewById(R.id.search_result_poi_view_address);
        m_detailsHeader = (View)m_view.findViewById(R.id.search_result_poi_view_details_header);
        m_phoneView = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone);
        m_webLinkView = (TextView)m_view.findViewById(R.id.search_result_poi_view_web_link);
        m_descriptionView = (TextView)m_view.findViewById(R.id.search_result_poi_view_descritption);
        m_poiImageHeader = (View)m_view.findViewById(R.id.search_result_poi_image_header);
        m_humanReadableTagsView = (TextView)m_view.findViewById(R.id.search_result_poi_view_tags);
        m_humanReadableTagsHeader = (View)m_view.findViewById(R.id.search_result_poi_view_tags_header);
        m_tagIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tag_icon);
		m_poiImage = (ImageView)m_view.findViewById(R.id.search_result_poi_view_image);
		m_poiImageGradient = m_view.findViewById(R.id.search_result_poi_view_image_gradient);
        m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_facebookUrl = (ImageView)m_view.findViewById(R.id.search_result_poi_view_facebook);
		m_twitterUrl = (ImageView)m_view.findViewById(R.id.search_result_poi_view_twitter);
		m_email = (ImageView)m_view.findViewById(R.id.search_result_poi_view_email);
		m_addressIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_address_icon);
		m_phoneIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_phone_icon);
		m_webIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_web_link_icon);
		m_tagsIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tags_icon);
		m_descriptionIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_description_icon);
		m_poiImageViewContainer = (View)m_view.findViewById(R.id.search_result_poi_view_image_container);
		m_dropPinText = (TextView)m_view.findViewById(R.id.drop_pin_text);
		m_contentContainer = (ScrollView)m_view.findViewById(R.id.content_container);
		m_footerFade = (ImageView)m_view.findViewById(R.id.footer_fade);
		m_linearContentContainer = (LinearLayout)m_view.findViewById(R.id.linear_content_container);
		m_webView = (WebView)m_view.findViewById(R.id.webview);
		m_webViewContainer = (View)m_view.findViewById(R.id.search_result_poi_view_webview_container);
        
        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        m_webView.setWebViewClient(new WebViewClient()
        {
            @Override
            public void onReceivedError(WebView view, int errorCode, String description, String failingUrl)
            {
                /*
                 * A lot of the examples suggest something like this:
                 * if(errorCode==404)
                 * However this does not give the expected results, instead use the defined constants:
                 * ERROR_HOST_LOOKUP
                 * ERROR_FILE_NOT_FOUND
                */

                view.loadUrl("file:///android_asset/page_not_found.html");
            }
        });
        
        m_closeButton.setOnClickListener(this);
        m_togglePinnedButton.setOnClickListener(this);
        m_facebookUrl.setOnClickListener(this);
        m_twitterUrl.setOnClickListener(this);
        m_email.setOnClickListener(this);

        m_activity.addBackButtonPressedListener(this);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
        m_activity.removeBackButtonPressedListener(this);
    }

    public void displayPoiInfo(
    		final String title,
    		final String subtitle,
    		final String address,
    		final String description,
    		final String phone, 
    		final String url,
    		final String iconKey,
    		final String[] humanReadableTags,
    		final String imageUrl,
    		final String vendor,
    		final boolean isPinned,
    		final String facebook,
    		final String twitter,
    		final String email,
    		final String customViewUrl,
    		final int customViewHeight) 
    {
    	int containerWidth = m_searchResultPoiViewContainer.getWidth();
    	int containerHeight = m_searchResultPoiViewContainer.getHeight();
    	int maxWidth = (int) (containerHeight * 0.5f);
    	if(m_searchResultPoiViewContainer.getWidth() > maxWidth)
    	{
    		m_searchResultPoiViewContainer.getLayoutParams().width = maxWidth;
    	}
    	m_url = url;
    	m_poiImageUrl = imageUrl;
    	
        m_titleView.setText(title);
        m_subtitleView.setText(subtitle);
        
        if(subtitle.equals(""))
        {
        	m_subtitleView.setVisibility(View.GONE);
        }
        else
        {
        	m_subtitleView.setVisibility(View.VISIBLE);
        }
        
        if(!address.equals("") || !phone.equals("") || !facebook.equals("") || !twitter.equals("") || !email.equals(""))
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
        	m_webLinkView.setVisibility(View.VISIBLE);
        	m_webIcon.setVisibility(View.VISIBLE);
        	m_webLinkView.setText(url.replace("", ""));
        	
        	final String webRegex = "[\\S]*";
        	Linkify.addLinks(m_webLinkView, Pattern.compile(webRegex), url);
        }
        else
        {
        	m_webLinkView.setVisibility(View.GONE);
        	m_webIcon.setVisibility(View.GONE);
        }

        m_poiImageProgressBar.setVisibility(View.GONE);
    	m_poiImageGradient.setVisibility(View.GONE);

        if(!imageUrl.equals(""))
        {
        	m_poiImageProgressBar.setVisibility(View.VISIBLE);
            setPoiImageVisibility(View.VISIBLE);
        }
        else
        {
            setPoiImageVisibility(View.GONE);
        }
        
        if(!facebook.equals(""))
        {
        	m_facebookUrl.setVisibility(View.VISIBLE);
        	m_facebookUrl.setTag(facebook);
        }
        else
        {
        	m_facebookUrl.setVisibility(View.GONE);
        }
        
        if(!twitter.equals(""))
        {
        	m_twitterUrl.setVisibility(View.VISIBLE);
        	m_twitterUrl.setTag(twitter);
        }
        else
        {
        	m_twitterUrl.setVisibility(View.GONE);
        }
        
        if(!email.equals(""))
        {
        	m_email.setVisibility(View.VISIBLE);
        	m_email.setTag(email);
        }
        else
        {
        	m_email.setVisibility(View.GONE);
        }
        
        if(humanReadableTags.length > 0)
        {
        	m_humanReadableTagsHeader.setVisibility(View.GONE);
        	m_humanReadableTagsView.setVisibility(View.VISIBLE);
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
        	m_humanReadableTagsHeader.setVisibility(View.GONE);
            m_humanReadableTagsView.setVisibility(View.GONE);
            m_tagsIcon.setVisibility(View.GONE);
        }
        
        if(!description.equals(""))
        {
            m_descriptionView.setVisibility(View.VISIBLE);
            m_descriptionIcon.setVisibility(View.VISIBLE);
            m_descriptionView.setText(description);
        }
        else
        {
        	m_descriptionView.setVisibility(View.GONE);
            m_descriptionIcon.setVisibility(View.GONE);
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
        
        if(!customViewUrl.equals(""))
        {
        	m_webView.loadUrl(customViewUrl);

            final int defaultViewHeight = 256;
            final int viewHeight = (customViewHeight != -1) ? customViewHeight : defaultViewHeight;
            
            RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams) m_webView.getLayoutParams();
            params.height = m_activity.dipAsPx(viewHeight);
            m_webView.setLayoutParams(params);

            m_webView.getSettings().setLoadWithOverviewMode(true);
        	m_webView.getSettings().setUseWideViewPort(true);
        	m_poiImageViewContainer.setVisibility(View.GONE);
        	m_webViewContainer.setVisibility(View.VISIBLE);
        	m_poiImageHeader.setVisibility(View.VISIBLE);
        }
    }
    
    public void handleButtonLink(View view)
    {
    	String url = (String)view.getTag();
    	if (!url.startsWith("http://") && !url.startsWith("https://"))
			   url = "http://" + url;
    	
		Intent intent = new Intent();
		intent.setAction(Intent.ACTION_VIEW);
		intent.addCategory(Intent.CATEGORY_BROWSABLE);
		intent.setData(Uri.parse(url));
		m_activity.startActivity(intent);
		m_handlingClick = false;
    }
    
    public void openEmailLink(View view)
    {
    	String url = (String)view.getTag();
    	
    	Intent intent = new Intent(Intent.ACTION_SEND);
    	intent.setType("plain/text");
    	intent.putExtra(Intent.EXTRA_EMAIL, new String[] { url });
    	intent.putExtra(Intent.EXTRA_SUBJECT, "");
    	intent.putExtra(Intent.EXTRA_TEXT, "");
    	m_activity.startActivity(Intent.createChooser(intent, ""));
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
        else if(view == m_facebookUrl || view == m_twitterUrl)
        {
        	handleButtonLink(view);
        }
        else if(view == m_email)
        {
        	openEmailLink(view);
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

                // result if BitmapFactory.decodeByteArray fails to convert to image
                if(poiBitmap == null)
                {
                    setPoiImageVisibility(View.GONE);
                }
                else
                {
                    if(m_poiImageViewContainer.getVisibility() != View.GONE)
                    {
                        m_poiImage.setImageBitmap(Bitmap.createBitmap(poiBitmap));
                    }
                }
			}
			else
			{
                setPoiImageVisibility(View.GONE);
			}
		}
		
		HandleFooterFadeInitialVisibility();
	}

	private void setPoiImageVisibility(int view)
    {
        m_poiImageHeader.setVisibility(view);
        m_poiImageViewContainer.setVisibility(view);
    }

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);
        m_togglePinnedButton.setOnClickListener(null);

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
