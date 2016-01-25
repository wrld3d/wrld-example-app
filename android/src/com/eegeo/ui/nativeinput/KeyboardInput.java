// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.ui.nativeinput;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;

public class KeyboardInput
{
    private static InputMethodManager m_inputManager;
    private static View m_targetView;

    public static void dismiss()
    {
        m_inputManager.hideSoftInputFromWindow(m_targetView.getWindowToken(), 0);
    }

    public static void showKeyboard(final Activity a, final int keyboardType, final int returnKeyType, final long ptr)
    {
        Log.v("ShowKeyboard", "Keyboard Type: " + keyboardType + ", Return Key Type: " + returnKeyType);

        a.runOnUiThread(new Runnable()
        {
            public void run()
            {
                try
                {
                    m_targetView = a.getWindow().getDecorView().getRootView();

                    Log.v("ShowKeyboard", "Forcing SoftInput Display");
                    m_inputManager = (InputMethodManager)a.getSystemService(Context.INPUT_METHOD_SERVICE);
                    m_inputManager.showSoftInput(m_targetView, InputMethodManager.SHOW_FORCED);
                }
                catch (Exception e)
                {
                    Log.v("KeyboardInput", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
                }
            }
        });
    }
}
