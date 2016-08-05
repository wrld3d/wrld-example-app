// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import com.eegeo.categories.CategoryResources;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.TintableImageView;
import com.eegeo.helpers.TintablePinToggleButton;
import com.eegeo.ProjectSwallowApp.R;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

public class MeetingRoomSearchResultPoiView implements View.OnClickListener 
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	private View m_view = null;
	private RelativeLayout m_uiRoot = null;

	// Availability Constants
	private final String MEETING_ROOM_AVAILABLE = "available";
	private final String MEETING_ROOM_AVAILABLE_SOON = "available_soon";
	private final String MEETING_ROOM_OCCUPIED = "occupied";

	private View m_closeButton = null;
	private View m_togglePinnedButton = null;
	private TextView m_titleView = null;
	private ImageView m_categoryIcon = null;
	private ImageView m_poiImage = null;
	private TintableImageView m_availableButton = null;
	private TintableImageView m_availableSoonButton = null;
	private TintableImageView m_occupiedButton = null;
	private View m_poiImageProgressBar = null;
	private String m_poiImageUrl;
	private String m_availability;

    private TintablePinToggleButton m_togglePinnedWrapper;

	public MeetingRoomSearchResultPoiView(MainActivity activity, long nativeCallerPointer) 
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;
	
		m_uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_meeting_room_layout, m_uiRoot, false);
		RelativeLayout.LayoutParams layoutParams = (LayoutParams) m_view.getLayoutParams();
		if (m_activity.getResources().getBoolean(R.bool.isPhone)) 
		{
			layoutParams.topMargin = layoutParams.bottomMargin = layoutParams.leftMargin = layoutParams.rightMargin = m_activity.dipAsPx(20);
		}
		else 
		{
			layoutParams.topMargin = layoutParams.bottomMargin = m_activity.dipAsPx(40);
			layoutParams.leftMargin = layoutParams.rightMargin = (int) (m_uiRoot.getWidth() * 0.3f);
		}
		m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
		m_togglePinnedButton = m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
		m_togglePinnedWrapper = new TintablePinToggleButton(m_togglePinnedButton);
		m_availableButton = (TintableImageView) m_view.findViewById(R.id.search_result_poi_view_button_available);
		m_availableSoonButton = (TintableImageView) m_view.findViewById(R.id.search_result_poi_view_button_available_soon);
		m_occupiedButton = (TintableImageView) m_view.findViewById(R.id.search_result_poi_view_button_occupied);
		m_titleView = (TextView) m_view.findViewById(R.id.search_result_poi_view_title);
		m_categoryIcon = (ImageView) m_view.findViewById(R.id.search_result_poi_view_category_icon);
		m_poiImageProgressBar = m_view.findViewById(R.id.search_result_poi_view_image_progress);
		m_poiImage = (ImageView) m_view.findViewById(R.id.search_result_poi_view_image);
	
		m_activity.recursiveDisableSplitMotionEvents((ViewGroup) m_view);
	
		m_view.setVisibility(View.GONE);
		m_uiRoot.addView(m_view);
	
		m_closeButton.setOnClickListener(this);
		m_togglePinnedButton.setOnClickListener(this);
		m_availableButton.setOnClickListener(this);
		m_availableSoonButton.setOnClickListener(this);
		m_occupiedButton.setOnClickListener(this);
	}
	
	public void destroy() 
	{
		m_uiRoot.removeView(m_view);
	}

	public void displayPoiInfo(final String title, final String availability, final String category,
			final String imageUrl, final boolean isPinned) 
	{
		m_poiImageUrl = imageUrl;
		m_availability = availability;
		SharedPreferences pref = m_activity.getPreferences(Context.MODE_PRIVATE);
		if (pref.contains(title)) 
		{
			m_availability = (String) pref.getAll().get(title);
		}

		m_titleView.setText(title);

		m_poiImage.setVisibility(View.GONE);
		m_poiImageProgressBar.setVisibility(View.GONE);

		if (!imageUrl.equals("")) 
		{
			m_poiImageProgressBar.setVisibility(View.VISIBLE);
		}

		int iconId = CategoryResources.getSmallIconForCategory(m_activity, category);
		m_categoryIcon.setImageResource(iconId);

		m_closeButton.setEnabled(true);
		m_togglePinnedWrapper.setPinToggleState(isPinned);
		m_togglePinnedButton.setVisibility(View.GONE);

		refreshOccupancyButtonStates();

		m_view.setVisibility(View.VISIBLE);
		m_view.requestFocus();
	}

    public void onClick(View view)
    {
        if(view == m_closeButton)
        {
			handleCloseClicked();
		} 
        else if (view == m_togglePinnedButton) 
		{
			handleTogglePinnedClicked();
		} 
        else if (view == m_availableButton) 
        {
			handleAvailableButtonSelected();
		} 
        else if (view == m_availableSoonButton) 
        {
			handleAvailableSoonButtonSelected();
		} 
        else if (view == m_occupiedButton) 
        {
			handleOccupiedButtonSelected();
		}
	}

	public void dismissPoiInfo() 
	{
		m_view.setVisibility(View.GONE);
	}

	public void updateImageData(String url, boolean hasImage, final byte[] imgData) 
	{
		if (url.equals(m_poiImageUrl)) 
		{
			m_poiImageProgressBar.setVisibility(View.GONE);

			if (hasImage) 
			{
				m_poiImage.setVisibility(View.VISIBLE);

				BitmapFactory.Options bmOptions = new BitmapFactory.Options();
				bmOptions.inJustDecodeBounds = true;
				bmOptions.inJustDecodeBounds = false;
				bmOptions.inPurgeable = true;

				int size = m_view.getWidth();
				Bitmap poiBitmap = BitmapFactory.decodeByteArray(imgData, 0, imgData.length, bmOptions);
				m_poiImage.setImageBitmap(Bitmap.createScaledBitmap(poiBitmap, size, size, false));
			}
		}
	}

	private void handleAvailableButtonSelected() 
	{
		m_availability = MEETING_ROOM_AVAILABLE;
		persistMeetingRoomState(m_availability);
		refreshOccupancyButtonStates();
		SearchResultPoiViewJniMethods.AvailabilityChanged(m_nativeCallerPointer, m_availability);
	}

	private void handleAvailableSoonButtonSelected() 
	{
		m_availability = MEETING_ROOM_AVAILABLE_SOON;
		persistMeetingRoomState(m_availability);
		refreshOccupancyButtonStates();
		SearchResultPoiViewJniMethods.AvailabilityChanged(m_nativeCallerPointer, m_availability);
	}

	private void handleOccupiedButtonSelected() 
	{
		m_availability = MEETING_ROOM_OCCUPIED;
		persistMeetingRoomState(m_availability);
		refreshOccupancyButtonStates();
		SearchResultPoiViewJniMethods.AvailabilityChanged(m_nativeCallerPointer, m_availability);
	}

	private void persistMeetingRoomState(String avalability) 
	{

	}

	private void refreshOccupancyButtonStates() 
	{
		m_availableButton.setSelected(m_availability.equals(MEETING_ROOM_AVAILABLE));
		m_availableSoonButton.setSelected(m_availability.equals(MEETING_ROOM_AVAILABLE_SOON));
		m_occupiedButton.setSelected(m_availability.equals(MEETING_ROOM_OCCUPIED));
	}

	private void handleCloseClicked() 
	{
		m_view.setEnabled(false);
		m_togglePinnedButton.setOnClickListener(null);

		SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
	}

	public static int calculateInSampleSize(BitmapFactory.Options options, int reqWidth, int reqHeight) 
	{
		// Raw height and width of image
		final int height = options.outHeight;
		final int width = options.outWidth;
		int inSampleSize = 1;

		if (height > reqHeight || width > reqWidth) 
		{
			final int halfHeight = height / 2;
			final int halfWidth = width / 2;

			// Calculate the largest inSampleSize value that is a power of 2 and
			// keeps both
			// height and width larger than the requested height and width.
			while ((halfHeight / inSampleSize) > reqHeight && (halfWidth / inSampleSize) > reqWidth) 
			{
				inSampleSize *= 2;
			}
		}

		return inSampleSize;
	}

	private void handleTogglePinnedClicked() 
	{
		if (m_togglePinnedWrapper.isPinned()) 
		{
			showRemovePinDialog();
		} 
		else 
		{
			SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
			m_togglePinnedWrapper.setPinToggleState(true);
		}
	}

	private void showRemovePinDialog() 
	{
		AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
		builder.setTitle("Remove Pin").setMessage("Are you sure you want to remove this pin?")
				.setPositiveButton("Yes,  delete it", new DialogInterface.OnClickListener() 
				{
					@Override
					public void onClick(DialogInterface dialog, int id) 
					{
						SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
						m_togglePinnedWrapper.setPinToggleState(false);
					}
				}).setNegativeButton("No,  keep it", new DialogInterface.OnClickListener() 
				{
					@Override
					public void onClick(DialogInterface dialog, int which) 
					{
						m_togglePinnedWrapper.setPinToggleState(true);
					}
				}).setOnCancelListener(new DialogInterface.OnCancelListener() 
				{
					@Override
					public void onCancel(DialogInterface dialog) 
					{
						m_togglePinnedWrapper.setPinToggleState(true);
					}
				});
		AlertDialog dialog = builder.create();
		dialog.show();
	}
}
