package com.eegeo.mypincreationdetails;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.text.Html;
import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.eegeo.helpers.IActivityIntentResultHandler;
import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.photos.PhotoIntentDispatcher;

public class MyPinCreationDetailsView implements View.OnClickListener, IActivityIntentResultHandler
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
	protected TextView m_termsAndConditionsLink = null;
	
	private Uri m_currentImageUri = null;
	private boolean m_awaitingIntentResponse;

	private final int JPEG_QUALITY = 90;
	private final String TERMS_AND_CONDITIONS_LINK = "http://sdk.eegeo.com";
	
	public MyPinCreationDetailsView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		createView();
	}
	
	public void destroy()
	{
		final IActivityIntentResultHandler thisHandler = this;
		
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		uiRoot.removeView(m_view);
		m_view = null;
		
		m_activity.getPhotoIntentDispatcher().removeActivityIntentResultHandler(thisHandler);
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
		m_termsAndConditionsLink = (TextView)m_view.findViewById(R.id.poi_creation_details_terms_conditions_link);
		
		m_view.setVisibility(View.GONE);
		
		m_termsAndConditionsLink.setClickable(true);
		m_termsAndConditionsLink.setMovementMethod(LinkMovementMethod.getInstance());
		String linkText = "<a href='" + TERMS_AND_CONDITIONS_LINK + "'>(Terms & Conditions)</a>";
		m_termsAndConditionsLink.setText(Html.fromHtml(linkText));
		
		m_activity.getPhotoIntentDispatcher().addActivityIntentResultHandler(this);
		
		uiRoot.addView(m_view);
	}
	
	public void show()
	{
		m_view.setVisibility(View.VISIBLE);
		m_view.requestFocus();
		
		m_poiImage.setImageResource(R.drawable.image_blank);
		m_title.setText("");
		m_description.setText("");
		
		m_currentImageUri = null;
		
		m_awaitingIntentResponse = false;;
	}
	
	public void dismiss()
	{
		m_view.setVisibility(View.GONE);
	}

	@Override
	public void onClick(final View view) 
	{
		if(view == m_takePhotoButton)
		{
			if(m_awaitingIntentResponse)
			{
				return;
			}
			
			m_activity.getPhotoIntentDispatcher().takePhoto();
			
			m_awaitingIntentResponse = true;
		}
		else if(view == m_selectFromGalleryButton)
		{
			if(m_awaitingIntentResponse)
			{
				return;
			}
			
			m_activity.getPhotoIntentDispatcher().selectPhotoFromGallery();
			m_awaitingIntentResponse = true;
		}
		else if(view == m_closeButton)
		{
			MyPinCreationDetailsJniMethods.CloseButtonPressed(m_nativeCallerPointer);
		}
		else if(view == m_submitButton)
		{
			String titleText = m_title.getText().toString();
			titleText = titleText.isEmpty() ? "Untitled Pin" : titleText;
			String descriptionText = m_description.getText().toString();
			descriptionText = descriptionText.isEmpty() ? "No description" : descriptionText;
			
			byte[] byteArray = null;
			
			if(m_currentImageUri != null)
			{
				try
				{
					Bitmap bitmap = decodeImage();
					
					ByteArrayOutputStream stream = new ByteArrayOutputStream();
					bitmap.compress(Bitmap.CompressFormat.JPEG, JPEG_QUALITY, stream);
					byteArray = stream.toByteArray();
					stream.close();
					
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
			}
			
			Boolean shouldShare = m_shouldShareButton.isChecked();
			String uriPath = m_currentImageUri != null ? m_currentImageUri.toString() : "";
			MyPinCreationDetailsJniMethods.SubmitButtonPressed(m_nativeCallerPointer, titleText, descriptionText, uriPath, byteArray, shouldShare);
		}
	}

	@Override
	public void onActivityResult(final int requestCode, final int resultCode, final Intent data)
	{
		if(requestCode == PhotoIntentDispatcher.REQUEST_IMAGE_CAPTURE && resultCode == MainActivity.RESULT_OK)
		{
			Intent mediaScanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
			Uri contentUri = m_activity.getPhotoIntentDispatcher().getCurrentPhotoPath();
			mediaScanIntent.setData(contentUri);
			m_activity.sendBroadcast(mediaScanIntent);
			
			m_currentImageUri = contentUri;
			
			try 
			{
				Bitmap bitmap = decodeImage();
				m_poiImage.setImageBitmap(bitmap);
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
			
			
			
		}
		else if(requestCode == PhotoIntentDispatcher.SELECT_PHOTO_FROM_GALLERY && resultCode == MainActivity.RESULT_OK)
		{
			Uri selectedUri = data.getData();
			m_currentImageUri = selectedUri;
			
			try 
			{
				Bitmap bitmap = decodeImage();
				m_poiImage.setImageBitmap(bitmap);
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
		}
		
		if(requestCode == PhotoIntentDispatcher.SELECT_PHOTO_FROM_GALLERY || requestCode == PhotoIntentDispatcher.REQUEST_IMAGE_CAPTURE)
		{
			m_awaitingIntentResponse = false;
		}
	}
	
	private Bitmap decodeImage() throws IOException
	{
		final int idealSizePx = 512;
		
		InputStream is = m_activity.getContentResolver().openInputStream(m_currentImageUri);
		
		BitmapFactory.Options bmOptions = new BitmapFactory.Options();
		bmOptions.inJustDecodeBounds = true;
		
		Bitmap bitmap = BitmapFactory.decodeStream(is, null, bmOptions);
		is.close();
		int photoWidth = bmOptions.outWidth;
		int photoHeight = bmOptions.outHeight;
		
		int scaleFactor = Math.min(photoWidth/idealSizePx, photoHeight/idealSizePx);
		bmOptions.inJustDecodeBounds = false;
		bmOptions.inSampleSize = scaleFactor;
		bmOptions.inPurgeable = true;
		
		is = m_activity.getContentResolver().openInputStream(m_currentImageUri);
		bitmap = BitmapFactory.decodeStream(is, null, bmOptions);
		is.close();
		
		return bitmap;
	}
	
	
}
