package com.eegeo.helpers;

import android.content.Context;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.LightingColorFilter;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LayerDrawable;
import android.util.AttributeSet;
import android.widget.ImageView;

public class TintableImageView extends ImageView 
{
    public TintableImageView(Context context) {
        super(context);
    }

    public TintableImageView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public TintableImageView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }
    
    @Override
    public void setBackgroundDrawable(Drawable d) {
    	super.setBackgroundDrawable(new TintableImageViewLayerDrawable(d));
    }

	protected class TintableImageViewLayerDrawable extends LayerDrawable 
	{
		protected ColorFilter m_pressedFilter = new LightingColorFilter(Color.DKGRAY, 1);
		
		public TintableImageViewLayerDrawable(Drawable d) {
			super(new Drawable[] { d });
		}
  
		@Override
		protected boolean onStateChange(int[] states) 
		{
			boolean enabled = false;
			boolean pressed = false;

			for (int state : states) 
			{
				if (state == android.R.attr.state_enabled) {
					enabled = true;
				}
				else if (state == android.R.attr.state_pressed) {
					pressed = true;
				}
			}

			mutate();
    
			if (enabled && pressed) 
			{
				setColorFilter(m_pressedFilter);
			}
			else if (!enabled) 
			{
				// do any other disabled effect here
				setColorFilter(null);
			} 
			else 
			{
				setColorFilter(null);
			}

			invalidateSelf();

			return super.onStateChange(states);
		}

		@Override
		public boolean isStateful() {
			return true;
		}
	}
}
