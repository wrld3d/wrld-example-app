package com.eegeo;

import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.app.Activity;
import android.content.res.AssetManager;

public class MainActivity extends Activity implements SurfaceHolder.Callback
{
    private EegeoSurfaceView m_surfaceView;
    private SurfaceHolder m_surfaceHolder;
    private long m_nativeAppWindowPtr;
    
    public static native long startNativeCode(MainActivity activity, AssetManager assetManager, float dpi);
    public static native void stopNativeCode();
    public static native void pauseNativeCode();
    public static native void resumeNativeCode();
    public static native void setNativeSurface(Surface surface);
    
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        System.loadLibrary("native-activity");
        
        setContentView(R.layout.activity_main);  

        m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
        m_surfaceView.getHolder().addCallback(this);
    }
    
    @Override
    protected void onStart() 
    {
        super.onStart();
        
        DisplayMetrics dm = getResources().getDisplayMetrics();
		float dpi = dm.ydpi;
        
        m_nativeAppWindowPtr = startNativeCode(this, getAssets(), dpi);
        
        if(m_nativeAppWindowPtr == 0)
        {
        	throw new RuntimeException("Failed to start native code.");
        }
    }

    @Override
    protected void onResume() 
    {
        super.onResume();
        resumeNativeCode();
        
        if(m_surfaceHolder != null)
        {
        	setNativeSurface(m_surfaceHolder.getSurface());
        }
    }
    
    @Override
    protected void onPause() 
    {
        pauseNativeCode();
        super.onPause();
    }

    @Override
    protected void onStop() 
    {
        super.onStop();
        stopNativeCode();
        m_nativeAppWindowPtr = 0;
    }

	@Override
	public void surfaceCreated(SurfaceHolder holder) 
	{
		//nothing to do
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) 
	{
		m_surfaceHolder = null;
		setNativeSurface(null);
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) 
	{
		m_surfaceHolder = holder;
		setNativeSurface(m_surfaceHolder.getSurface());
	}
}