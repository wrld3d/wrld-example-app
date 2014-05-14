package com.eegeo;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceView;

public class EegeoSurfaceView extends SurfaceView 
{
    public static native void processNativePointerDown(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
    public static native void processNativePointerUp(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
    public static native void processNativePointerMove(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);

	public EegeoSurfaceView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent e) 
	{
        //we need to convert multi-touch event handling into struct of arrays for many pointers to send over JNI
    	
    	//C++ event representation is like;
    	/*
			float x, y;
			int pointerIdentity;
			int pointerIndex;
    	 */
    	   
    	int pointerCount = e.getPointerCount();
    	int primaryActionIndex = e.getActionIndex();
    	int primaryActionIdentifier = e.getPointerId(primaryActionIndex);
    	
    	float[] xArray = new float[pointerCount];
    	float[] yArray = new float[pointerCount];
    	int[] pointerIdentityArray = new int[pointerCount];
    	int[] pointerIndexArray = new int[pointerCount];
    	
    	for(int pointerIndex = 0; pointerIndex < pointerCount; ++pointerIndex)
    	{
            xArray[pointerIndex] = e.getX(pointerIndex);
            yArray[pointerIndex] = e.getY(pointerIndex);
            pointerIdentityArray[pointerIndex] = e.getPointerId(pointerIndex);
            pointerIndexArray[pointerIndex] = pointerIndex;
        }
    	
	    switch (e.getActionMasked()) 
	    {
	        case MotionEvent.ACTION_DOWN:
	        case MotionEvent.ACTION_POINTER_DOWN:
	        {	
	        	processNativePointerDown(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
	        }break;

	        case MotionEvent.ACTION_POINTER_UP:
	        case MotionEvent.ACTION_UP:
	        {      
	        	processNativePointerUp(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
	        }  break;
	        
	        case MotionEvent.ACTION_MOVE:
	        {	 
	        	processNativePointerMove(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
	        }break;
	    }
    
	    return true;
	}
}
