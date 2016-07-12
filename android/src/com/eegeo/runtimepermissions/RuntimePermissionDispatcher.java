// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.runtimepermissions;

import java.util.ArrayList;
import java.util.List;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IRuntimePermissionResultHandler;
import com.eegeo.mypincreationdetails.MyPinCreationDetailsView;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

// This class handles the dispatching of runtime permissions
public class RuntimePermissionDispatcher
{
    public static final int CAMERA_PERMISSION_REQUEST_CODE = 50;
    public static final int GPS_PERMISSION_REQUEST_CODE = 51;

    private MainActivity m_activity = null;
    private List<IRuntimePermissionResultHandler> m_activityCallbacks = new ArrayList<IRuntimePermissionResultHandler>();

    public RuntimePermissionDispatcher(MainActivity activity)
    {
        m_activity = activity;
    }
    
    public void addRuntimePermissionResultHandler(IRuntimePermissionResultHandler handler)
    {
        if(!m_activityCallbacks.contains(handler))
        {
            m_activityCallbacks.add(handler);
        }
    }

    public void removeIRuntimePermissionResultHandler(IRuntimePermissionResultHandler handler)
    {
        if(m_activityCallbacks.contains(handler))
        {
            m_activityCallbacks.remove(handler);
        }
    }

    public boolean hasCameraAndStoragePermissions(MyPinCreationDetailsView myPinCreationDetailView)
    {
        if(ContextCompat.checkSelfPermission(m_activity,
                Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED
                && ContextCompat.checkSelfPermission(m_activity,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED)
        {
            return true;
        }
        else
        {
            ActivityCompat.requestPermissions(m_activity,
                    new String[] { Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE },
                    CAMERA_PERMISSION_REQUEST_CODE);
        }
        return false;
    }

    public boolean hasLocationPermissions()
    {
        if(ContextCompat.checkSelfPermission(m_activity,
                Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            return true;
        }
        else
        {
            ActivityCompat.requestPermissions(m_activity, new String[] { Manifest.permission.ACCESS_FINE_LOCATION },
                    GPS_PERMISSION_REQUEST_CODE);
        }
        return false;
    }

    public void startAppSettings(final Context context)
    {
        if(context == null)
        {
            return;
        }
        final Intent i = new Intent();
        i.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
        i.addCategory(Intent.CATEGORY_DEFAULT);
        i.setData(Uri.parse("package:" + context.getPackageName()));
        i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        i.addFlags(Intent.FLAG_ACTIVITY_NO_HISTORY);
        i.addFlags(Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
        context.startActivity(i);
    }

    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        if(requestCode != CAMERA_PERMISSION_REQUEST_CODE && requestCode != GPS_PERMISSION_REQUEST_CODE)
            return;

        for (IRuntimePermissionResultHandler handler : m_activityCallbacks)
        {
            handler.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

}
