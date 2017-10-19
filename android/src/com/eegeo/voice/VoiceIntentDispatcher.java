// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.voice;

import android.content.Intent;
import android.speech.RecognizerIntent;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IActivityIntentResultHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

// This class handles the dispatching of intents related to voice controls
public class VoiceIntentDispatcher {

    public static final int REQ_CODE_SPEECH_INPUT = 100;

    private MainActivity m_activity = null;
    private List<IActivityIntentResultHandler> m_activityCallbacks = new ArrayList<IActivityIntentResultHandler>();

    public VoiceIntentDispatcher(MainActivity activity)
    {
        m_activity = activity;
    }

    public void listenToVoice()
    {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "asking for voice authorisation");
        m_activity.startActivityForResult(intent, REQ_CODE_SPEECH_INPUT);
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
        if(requestCode != REQ_CODE_SPEECH_INPUT)
        {
            return;
        }

        for(IActivityIntentResultHandler handler : m_activityCallbacks)
        {
            handler.onActivityResult(requestCode, resultCode, data);
        }
    }
}
