package com.eegeo.poicreationdetails;

import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class PoiCreationDetailsView implements View.OnClickListener
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	protected RelativeLayout m_view = null;
	protected Button m_closeButton = null;
	protected Button m_takePhotoButton = null;
	protected Button m_selectFromGalleryButton = null;
	protected Button m_submitButton = null;
	
	public PoiCreationDetailsView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				createView();
			}
		});
	}
	
	public void destroy()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
			}
		});
	}
	
	private void createView()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = (RelativeLayout)m_activity.getLayoutInflater().inflate(R.layout.poi_creation_details_layout, uiRoot, false);
		
		m_closeButton = (Button)m_view.findViewById(R.id.poi_creation_details_button_close);
		m_closeButton.setOnClickListener(this);
		m_submitButton = (Button)m_view.findViewById(R.id.poi_creation_details_button_submit);
		m_submitButton.setOnClickListener(this);
		m_takePhotoButton = (Button)m_view.findViewById(R.id.poi_creation_details_button_photo);
		m_takePhotoButton.setOnClickListener(this);
		m_selectFromGalleryButton = (Button)m_view.findViewById(R.id.poi_creation_details_button_gallery);
		m_selectFromGalleryButton.setOnClickListener(this);
		
		m_view.setVisibility(View.GONE);
		uiRoot.addView(m_view);
	}
	
	public void show()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				m_view.setVisibility(View.VISIBLE);
				m_view.requestFocus();
			}
		});	
	}
	
	public void dismiss()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				m_view.setVisibility(View.GONE);
			}
		});	
	}

	@Override
	public void onClick(final View view) 
	{
		m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				if(view == m_closeButton)
				{
					PoiCreationDetailsJniMethods.CloseButtonPressed(m_nativeCallerPointer);
				}
				else if(view == m_submitButton)
				{
					//PoiCreationDetailsJniMethods.SubmitButtonPressed(m_nativeCallerPointer); // Pass strings & bool!
				}
				else if(view == m_takePhotoButton)
				{
					// Take a photo and set its source.
				}
				else if(view == m_selectFromGalleryButton)
				{
					// Select photo from gallery & set its source
				}
			}
		});
		
	}
}
