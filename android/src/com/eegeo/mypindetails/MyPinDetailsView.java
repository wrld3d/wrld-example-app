package com.eegeo.mypindetails;

import java.io.File;

import android.net.Uri;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class MyPinDetailsView implements View.OnClickListener
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	private View m_view = null;
	private RelativeLayout m_uiRoot = null;
	private View m_closeButton = null;
	private TextView m_titleView = null;
	private TextView m_descriptionView = null;
	private TextView m_descriptionHeader = null;
	private ImageView m_imageView = null;
	private TextView m_imageHeader = null;

	public MyPinDetailsView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.my_pin_details_layout, m_uiRoot, false);
		m_closeButton = m_view.findViewById(R.id.my_pin_details_view_close_button);
		m_titleView = (TextView)m_view.findViewById(R.id.my_pin_details_view_title);
		m_descriptionView = (TextView)m_view.findViewById(R.id.my_pin_details_view_description);
		m_descriptionHeader = (TextView)m_view.findViewById(R.id.my_pin_details_view_description_header);
		m_imageView = (ImageView)m_view.findViewById(R.id.my_pin_details_view_image);
		m_imageHeader = (TextView)m_view.findViewById(R.id.my_pin_details_view_image_header);
		
		m_closeButton.setOnClickListener(this);
		m_view.setVisibility(View.GONE);
		m_uiRoot.addView(m_view);
	}

	public void destroy()
	{
		m_uiRoot.removeView(m_view);
	}

	public void display(final String title, final String description, final String imagePath)
	{
		m_titleView.setText(title);

		if(!description.isEmpty())
		{
			m_descriptionView.setVisibility(View.VISIBLE);
			m_descriptionHeader.setVisibility(View.VISIBLE);
			m_descriptionView.setText(description);
		}
		else
		{
			m_descriptionView.setVisibility(View.GONE);
			m_descriptionHeader.setVisibility(View.GONE);
		}

		if(!imagePath.isEmpty())
		{
			m_imageHeader.setVisibility(View.VISIBLE);
			m_imageView.setVisibility(View.VISIBLE);
			
			String rootPath = m_activity.getFilesDir().getAbsolutePath();
			File imageFile = new File(rootPath + File.separator + imagePath);
			m_imageView.setImageURI(Uri.fromFile(imageFile));
		}
		else
		{
			m_imageView.setVisibility(View.GONE);
			m_imageHeader.setVisibility(View.GONE);
		}

		m_closeButton.setEnabled(true);
		m_view.setVisibility(View.VISIBLE);
		m_view.requestFocus();
	}

	public void dismiss()
	{
		m_view.setVisibility(View.GONE);
	}

	public void onClick(View view)
	{
		m_view.setEnabled(false);

		MyPinDetailsJniMethods.CloseButtonClicked(m_nativeCallerPointer);
	}
}
