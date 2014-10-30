// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.mobileexampleapp;

import android.os.IBinder;
import android.view.SurfaceHolder;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.app.Activity;
import android.content.Context;

public abstract class MainActivity extends Activity implements SurfaceHolder.Callback, INativeMessageRunner
{
	// http://developer.android.com/guide/practices/screens_support.html#dips-pels 
	// and http://stackoverflow.com/a/9904844
	public int pxAsDip(float px)
	{
		float density = getResources().getDisplayMetrics().density;
		int dip = (int)((px / density) + 0.5f);
		return dip;
	}
	
	public int dipAsPx(float dip)
	{
		float density = getResources().getDisplayMetrics().density;
		int px = (int)((dip * density) + 0.5f);
		return px;
	}
	
	public void dismissKeyboard(IBinder binder)
	{
		InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(binder, 0);
    	getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
	}
}
