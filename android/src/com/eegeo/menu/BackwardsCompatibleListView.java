// Copyright eeGeo Ltd (2012-2017), All Rights Reserved
package com.eegeo.menu;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.os.Build;
import android.util.AttributeSet;
import android.widget.ListView;

public class BackwardsCompatibleListView extends ListView
{
	public BackwardsCompatibleListView(Context context)
	{
		super(context);
	}
	
	public BackwardsCompatibleListView(Context context, AttributeSet attrs)
	{
        super(context, attrs);
    }

    public BackwardsCompatibleListView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

	private Rect m_clipBounds;

	@Override
	public void draw(Canvas canvas)
	{
	    if (m_clipBounds != null)
	    {
	        canvas.clipRect(m_clipBounds);
	    }
	    super.draw(canvas);
	}

	@Override
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
	public void setClipBounds(Rect clipBounds)
	{
	    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2)
	    {
	        super.setClipBounds(clipBounds);
	        return;
	    }

	    if (clipBounds != null)
	    {
	        if (clipBounds.equals(m_clipBounds))
	        {
	            return;
	        }
	        if (m_clipBounds == null)
	        {
	            invalidate();
	            m_clipBounds = new Rect(clipBounds);
	        }
	        else
	        {
	            invalidate(Math.min(m_clipBounds.left, clipBounds.left),
	                    Math.min(m_clipBounds.top, clipBounds.top),
	                    Math.max(m_clipBounds.right, clipBounds.right),
	                    Math.max(m_clipBounds.bottom, clipBounds.bottom));
	            m_clipBounds.set(clipBounds);
	        }
	    }
	    else 
	    {
	        if (m_clipBounds != null)
	        {
	            invalidate();
	            m_clipBounds = null;
	        }
	    }
	}

	@Override
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
	public Rect getClipBounds()
	{
	    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2)
	    {
	        return super.getClipBounds();
	    }
	    else
	    {
	        return (m_clipBounds != null) ? new Rect(m_clipBounds) : null;
	    }
	}
}
