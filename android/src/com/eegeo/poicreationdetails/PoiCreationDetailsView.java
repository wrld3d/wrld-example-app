package com.eegeo.poicreationdetails;

import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.ToggleButton;

import com.eegeo.helpers.IActivityIntentResultHandler;
import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.photos.PhotoIntentDispatcher;

public class PoiCreationDetailsView implements View.OnClickListener, IActivityIntentResultHandler
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	protected RelativeLayout m_view = null;
	protected Button m_closeButton = null;
	protected Button m_takePhotoButton = null;
	protected Button m_selectFromGalleryButton = null;
	protected Button m_submitButton = null;
	protected ImageView m_poiImage = null;
	protected EditText m_title = null;
	protected EditText m_description = null;
	protected ToggleButton m_shouldShareButton = null;
	
	private Uri m_currentImageUri = null;
	
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
		final IActivityIntentResultHandler thisHandler = this;
		
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
				
				m_activity.getPhotoIntentDispatcher().removeActivityIntentResultHandler(thisHandler);
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
		m_poiImage = (ImageView)m_view.findViewById(R.id.poi_creation_details_image);
		m_title = (EditText)m_view.findViewById(R.id.poi_creation_details_title);
		m_description = (EditText)m_view.findViewById(R.id.poi_creation_details_description);
		m_shouldShareButton = (ToggleButton)m_view.findViewById(R.id.poi_creation_details_share_togglebutton);
		
		m_view.setVisibility(View.GONE);
		
		m_activity.getPhotoIntentDispatcher().addActivityIntentResultHandler(this);
		
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
				
				m_poiImage.setImageResource(R.drawable.image_blank);
				m_title.setText("");
				m_description.setText("");
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
		if(view == m_takePhotoButton)
		{
			m_activity.getPhotoIntentDispatcher().takePhoto();
		}
		else if(view == m_selectFromGalleryButton)
		{
			m_activity.getPhotoIntentDispatcher().selectPhotoFromGallery();
		}
		else
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
						String titleText = m_title.getText().toString();
						String descriptionText = m_description.getText().toString();
						String imagePath = "";
						if(m_currentImageUri != null)
						{
							imagePath = getRealPathFromURI(m_currentImageUri);
						}
						Boolean shouldShare = m_shouldShareButton.isChecked();
						PoiCreationDetailsJniMethods.SubmitButtonPressed(m_nativeCallerPointer, titleText, descriptionText, imagePath, shouldShare);
					}
				}
			});
		}
	}

	@Override
	public void onActivityResult(final int requestCode, final int resultCode, final Intent data)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				if(requestCode == PhotoIntentDispatcher.REQUEST_IMAGE_CAPTURE && resultCode == MainActivity.RESULT_OK)
				{
					Intent mediaScanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
					Uri contentUri = m_activity.getPhotoIntentDispatcher().getCurrentPhotoPath();
					mediaScanIntent.setData(contentUri);
					m_activity.sendBroadcast(mediaScanIntent);
					
					m_poiImage.setImageURI(contentUri);
					m_currentImageUri = contentUri;
				}
				else if(requestCode == PhotoIntentDispatcher.SELECT_PHOTO_FROM_GALLERY && resultCode == MainActivity.RESULT_OK)
				{
					Uri selectedUri = data.getData();
					m_poiImage.setImageURI(selectedUri);
					m_currentImageUri = selectedUri;
				}
			}
		});
		
	}
	
	private String getRealPathFromURI(Uri contentUri)
	{
		String[] proj = { MediaStore.Images.Media.DATA };
		
		Cursor cursor = m_activity.getContentResolver().query(contentUri, proj, null, null, null);
		if(cursor == null)
		{
			return contentUri.getPath();
		}
		int columnIndex = cursor.getColumnIndexOrThrow(proj[0]);
		cursor.moveToFirst();
		String result = cursor.getString(columnIndex);
		cursor.close();
		return result;
	}
}
