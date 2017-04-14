// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.surveys;

import com.eegeo.entrypointinfrastructure.MainActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;

public class SurveyView {
	
	private MainActivity m_activity = null;
	private static AlertDialog m_options = null;

	public SurveyView(MainActivity activity) {
		m_activity = activity;
	}
	
	protected void startUxCallback(String timerSurveyUrl)
	{
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);

        builder.setTitle("Want to help us improve our map?");
        builder.setMessage("Just a few quick questions - honest!");
        builder.setPositiveButton("Yes", showSurvey(timerSurveyUrl));
        builder.setNegativeButton("No", null);
        builder.setCancelable(false);

        m_options = builder.show();
	}
	
	private DialogInterface.OnClickListener showSurvey(final String timerSurveyUrl)
    {
        return new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                String prefixedUrl = "";
                if (!timerSurveyUrl.isEmpty())
                {
                    if (!timerSurveyUrl.startsWith("https://") && !timerSurveyUrl.startsWith("http://")) {
                        prefixedUrl = "http://" + timerSurveyUrl;
                    }
                    else
                    {
                        prefixedUrl = timerSurveyUrl;
                    }
                    Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(prefixedUrl));
                    m_activity.startActivity(browserIntent);
                }
                m_options = null;
            }
        };
    }
}
