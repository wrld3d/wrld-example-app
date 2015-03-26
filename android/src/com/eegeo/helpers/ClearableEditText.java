package com.eegeo.helpers;

import com.eegeo.mobileexampleapp.R;

import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class ClearableEditText extends RelativeLayout
{
	EditText m_editText;
	Button m_buttonClear;

	public ClearableEditText(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		initViews();
	}
	
	public ClearableEditText(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		initViews();
	}
	
	public ClearableEditText(Context context)
	{
		super(context);
		initViews();
	}
	
	void initViews()
	{
		LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		inflater.inflate(R.layout.clearable_edit_text, this, true);
		m_editText = (EditText) findViewById(R.id.clearable_edit);
		m_buttonClear = (Button) findViewById(R.id.clearable_button_clear);
		m_buttonClear.setVisibility(RelativeLayout.INVISIBLE);
		clearText();
		showHideClearButton();
	}
	
	void clearText()
	{
		m_buttonClear.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				m_editText.setText("");
			}
		});
	}
	
	void showHideClearButton()
	{
		m_editText.addTextChangedListener(new TextWatcher()
		{
			@Override
			public void onTextChanged(CharSequence s, int start, int before, int count)
			{
				if (s.length() > 0)
				{
					m_buttonClear.setVisibility(RelativeLayout.VISIBLE);
				}
				else
				{
					m_buttonClear.setVisibility(RelativeLayout.INVISIBLE);
				}
			}
			
			@Override
			public void beforeTextChanged(CharSequence s, int start, int count, int after)
			{
				// No implementation.
			}
	
			@Override
			public void afterTextChanged(Editable s)
			{
				// No implementation.
			}
		});
	}
	
	public Editable getText()
	{
		return m_editText.getText();
	}

	public void setImeActionLabel(String string, int keycodeEnter) 
	{
		m_editText.setImeActionLabel(string, keycodeEnter);
	}

	public void setOnEditorActionListener(TextView.OnEditorActionListener onEditorActionListener) 
	{
		m_editText.setOnEditorActionListener(onEditorActionListener);
	}
	
	public void setPlaceholder(String placeholder)
	{
		m_editText.setHint(placeholder);
	}
}