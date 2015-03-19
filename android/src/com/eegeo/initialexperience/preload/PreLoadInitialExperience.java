// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.initialexperience.preload;

import android.app.AlertDialog;
import android.content.DialogInterface;

import com.eegeo.entrypointinfrastructure.MainActivity;

public class PreLoadInitialExperience
{
    private MainActivity m_activity = null;
    private long m_nativeCallerPointer;
    private static AlertDialog m_options = null;

    public PreLoadInitialExperience(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_activity.runOnUiThread(new Runnable()
        {
            public void run()
            {
                AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);

                builder.setTitle("Pre-load San Francisco?");
                builder.setMessage("Select 'Yes' to pre-load data for the city of San Francisco. This message will not appear again.");
                builder.setPositiveButton("Yes", createClickListener(true));
                builder.setNegativeButton("No", createClickListener(false));
                builder.setCancelable(false);

                m_options = builder.show();
            }
        });
    }

    public void destroy()
    {
        m_activity.runOnUiThread(new Runnable()
        {
            public void run()
            {
                if(m_options != null)
                {
                    m_options.dismiss();
                    m_options = null;
                }
            }
        });
    }

    private DialogInterface.OnClickListener createClickListener(final boolean shouldPreload)
    {
        return new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                handleSelection(shouldPreload);
            }
        };
    }

    private void handleSelection(final boolean shouldPreload)
    {
        m_activity.runOnNativeThread(new Runnable()
        {
            public void run()
            {
                PreLoadInitialExperienceJniMethods.HandleSelection(m_nativeCallerPointer, shouldPreload);
            }
        });

        m_options = null;
    }
}
