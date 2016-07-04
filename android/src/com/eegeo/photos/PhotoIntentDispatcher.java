// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.photos;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import android.content.ContentValues;
import android.content.Intent;
import android.net.Uri;
import android.os.Build.VERSION_CODES;
import android.os.Environment;
import android.provider.MediaStore;

import com.eegeo.helpers.IActivityIntentResultHandler;
import com.eegeo.entrypointinfrastructure.MainActivity;

// This class handles the dispatching of intents related to fetching an image via photo or gallery selection.
public class PhotoIntentDispatcher
{
    public static final int REQUEST_IMAGE_CAPTURE = 1;
    public static final int SELECT_PHOTO_FROM_GALLERY = 2;

    private MainActivity m_activity = null;
    private List<IActivityIntentResultHandler> m_activityCallbacks = new ArrayList<IActivityIntentResultHandler>();
    private Uri m_currentPhotoPath;

    public PhotoIntentDispatcher(MainActivity activity)
    {
        m_activity = activity;
    }

    public boolean takePhoto()
    {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if(takePictureIntent.resolveActivity(m_activity.getPackageManager()) != null)
        {
        	// Due to FileUriExposedException on Android N and above, we will use content uri
        	if(android.os.Build.VERSION.SDK_INT >= VERSION_CODES.N)
        	{
        		try 
        		{
    		        ContentValues values = new ContentValues(1);
    		        values.put(MediaStore.Images.Media.MIME_TYPE, "image/jpg");
    		        m_currentPhotoPath = m_activity.getContentResolver()
    		                .insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);
    		    }
        		catch (Exception e) 
        		{
    		        e.printStackTrace();
    		    }
        	}
        	else
        	{
	            String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(new Date());
	            String filePath = timeStamp + ".jpg";
	            File file = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES), filePath);
	            m_currentPhotoPath = Uri.fromFile(file);
        	}
            takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, m_currentPhotoPath);
            m_activity.startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
            return true;
        }
        return false;
    }

    public void selectPhotoFromGallery()
    {
        Intent intent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        intent.setType("image/*");
        m_activity.startActivityForResult(intent, SELECT_PHOTO_FROM_GALLERY);
    }

    public void addActivityIntentResultHandler(IActivityIntentResultHandler handler)
    {
        if(!m_activityCallbacks.contains(handler))
        {
            m_activityCallbacks.add(handler);
        }
    }

    public void removeActivityIntentResultHandler(IActivityIntentResultHandler handler)
    {
        if(m_activityCallbacks.contains(handler))
        {
            m_activityCallbacks.remove(handler);
        }
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if(requestCode != REQUEST_IMAGE_CAPTURE && requestCode != SELECT_PHOTO_FROM_GALLERY)
            return;

        for(IActivityIntentResultHandler handler : m_activityCallbacks)
        {
            handler.onActivityResult(requestCode, resultCode, data);
        }
    }

    public Uri getCurrentPhotoPath()
    {
        return m_currentPhotoPath;
    }

}
