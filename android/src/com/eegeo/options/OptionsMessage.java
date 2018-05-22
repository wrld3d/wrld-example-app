package com.eegeo.options;

import android.view.View;
import android.widget.TextView;
import android.widget.RelativeLayout;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;

public class OptionsMessage
{
	private MainActivity m_activity;
	private RelativeLayout m_uiRoot;
	private View m_view;

	public interface OnClose
	{
		public void call();
	}

	public OptionsMessage(MainActivity activity, String title, String message, final OnClose onClose)
	{
		m_activity = activity;
		m_uiRoot = (RelativeLayout)activity.findViewById(R.id.ui_container);
		m_view = activity.getLayoutInflater().inflate(R.layout.message_layout, m_uiRoot, false);
		m_uiRoot.addView(m_view);

		TextView titleWidget = (TextView)m_view.findViewById(R.id.message_title);
		titleWidget.setText(title);

		TextView messageWidget = (TextView)m_view.findViewById(R.id.message_text);
		messageWidget.setText(message);

		View closeButton = m_view.findViewById(R.id.message_close_button);
		closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				onClose.call();
				m_uiRoot.removeView(m_view);
			}
		});
	}
}
