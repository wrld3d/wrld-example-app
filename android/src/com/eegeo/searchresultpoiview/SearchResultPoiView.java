// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.searchresultpoiview;

import java.util.regex.Pattern;

import android.text.util.Linkify;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.categories.CategoryResources;

public class SearchResultPoiView implements View.OnClickListener
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	private View m_view = null;
	private RelativeLayout m_uiRoot = null;
	private View m_closeButton = null;
	private TextView m_titleView = null;
	private TextView m_addressView = null;
	private TextView m_addressHeader = null;
	private TextView m_phoneView = null;
	private TextView m_phoneHeader = null;
	private TextView m_webView = null;
	private	TextView m_webHeader = null;
	private ImageView m_categoryIcon = null;

	public SearchResultPoiView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_layout, m_uiRoot, false);
		m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
		m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
		m_addressView = (TextView)m_view.findViewById(R.id.search_result_poi_view_address);
		m_addressHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_address_header);
		m_phoneView = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone);
		m_phoneHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_phone_header);
		m_webView = (TextView)m_view.findViewById(R.id.search_result_poi_view_web);
		m_webHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_web_header);
		m_categoryIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_category_icon);
		m_closeButton.setOnClickListener(this);
		m_view.setVisibility(View.GONE);
		m_uiRoot.addView(m_view);
	}

	public void destroy()
	{
		m_uiRoot.removeView(m_view);
	}

	public void displayPoiInfo(final String title, final String address, final String phone, final String url, final String category)
	{
		m_titleView.setText(title);

		if(!address.equals(""))
		{
			m_addressHeader.setVisibility(View.VISIBLE);
			m_addressView.setVisibility(View.VISIBLE);
			String addressText = address.replace(", ", "\n");
			m_addressView.setText(addressText);
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
			m_phoneView.setText(phone);

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
			m_webView.setVisibility(View.VISIBLE);
			m_webView.setText(url);
		}
		else
		{
			m_webHeader.setVisibility(View.GONE);
			m_webView.setVisibility(View.GONE);
		}

		int iconId = CategoryResources.getSmallIconForCategory(m_activity, category);
		m_categoryIcon.setImageResource(iconId);

		m_closeButton.setEnabled(true);
		m_view.setVisibility(View.VISIBLE);
		m_view.requestFocus();
	}

	public void dismissPoiInfo()
	{
		m_view.setVisibility(View.GONE);
	}

	public void onClick(View view)
	{
		m_view.setEnabled(false);

		SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
	}
}
