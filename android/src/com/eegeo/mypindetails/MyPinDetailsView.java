// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mypindetails;

import java.io.File;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewTreeObserver;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.ui.ScrollViewWithMaxHeight;

public class MyPinDetailsView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private View m_deleteButton = null;
    private TextView m_title = null;
    private TextView m_description = null;
    private ImageView m_image = null;
    private ScrollViewWithMaxHeight m_scrollSection = null;
    private RelativeLayout m_header = null;
    private RelativeLayout m_footer = null;
    private RelativeLayout m_headerSeparator = null;
    private RelativeLayout m_footerSeparator = null;
    private RelativeLayout m_scrollSectionSeparator = null;
    private RelativeLayout m_boundaryView = null;

    private String m_imagePath = "";

    private float m_imageWidth = 0.f;

    private boolean m_handlingClick = false;

    public MyPinDetailsView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.my_pin_details_layout, m_uiRoot, false);
        m_deleteButton = m_view.findViewById(R.id.my_pin_details_view_delete_button);
        m_closeButton = m_view.findViewById(R.id.my_pin_details_view_close_button);

        m_title = (TextView)m_view.findViewById(R.id.my_pin_details_view_title);
        m_image = (ImageView)m_view.findViewById(R.id.my_pin_details_view_image);
        m_description = (TextView)m_view.findViewById(R.id.my_pin_details_view_description_body);
        m_headerSeparator = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_header_separator);
        m_footerSeparator = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_footer_separator);
        m_scrollSectionSeparator = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_scroll_section_separator);

        m_header = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_header);
        m_footer = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_footer);
        m_boundaryView = (RelativeLayout)m_view.findViewById(R.id.my_pin_details_view_container);
        m_scrollSection = (ScrollViewWithMaxHeight)m_view.findViewById(R.id.my_pin_details_view_scroll_section);

        m_deleteButton.setOnClickListener(this);
        m_closeButton.setOnClickListener(this);
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);

        m_view.getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                if(m_footer.getHeight() > 0) {

                    m_scrollSection.set_maxSize(m_boundaryView.getHeight() - (m_header.getHeight() + m_headerSeparator.getHeight() + m_footer.getHeight() + m_footerSeparator.getHeight()));

                    RelativeLayout.LayoutParams footerParams = (RelativeLayout.LayoutParams)m_footer.getLayoutParams();
                    footerParams.addRule(RelativeLayout.BELOW, R.id.my_pin_details_view_footer_separator);
                    m_footer.setLayoutParams(footerParams);

                    m_imageWidth = m_scrollSection.getWidth() - (2*m_scrollSection.getPaddingLeft() + 2*m_scrollSection.getPaddingRight());

                    m_scrollSection.requestLayout();

                    if(!m_imagePath.isEmpty())
                    {
                        displayPinImage(m_imagePath);
                    }

                    m_view.getViewTreeObserver().removeOnGlobalLayoutListener(this);
                }
            }
        });
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void display(final String title, final String description, final String imagePath)
    {
        m_title.setText(title);
        m_description.setText(description);
        m_scrollSection.setScrollY(0);

        if(!imagePath.isEmpty())
        {
            if(m_imageWidth > 0)
            {
                displayPinImage(imagePath);
            }
            else
            {
                m_imagePath = imagePath;
            }
        }
        else
        {
            m_image.setVisibility(View.GONE);
            m_scrollSectionSeparator.setVisibility(View.GONE);
        }

        m_closeButton.setEnabled(true);
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
        m_handlingClick = false;
    }

    public void displayPinImage(final String imagePath)
    {
        String rootPath = m_activity.getFilesDir().getAbsolutePath();
        File imageFile = new File(rootPath + File.separator + imagePath);

        BitmapFactory.Options bmOptions = new BitmapFactory.Options();
        bmOptions.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(imageFile.getAbsolutePath(), bmOptions);
        int width = bmOptions.outWidth;
        int height = bmOptions.outHeight;
        float scaleRatio = m_imageWidth / (float)width;
        float viewHeight = height * scaleRatio;

        LayoutParams layout = m_image.getLayoutParams();
        layout.width = (int) m_imageWidth;
        layout.height = (int) viewHeight;
        m_image.setImageURI(Uri.fromFile(imageFile));
        m_image.setLayoutParams(layout);

        m_image.setVisibility(View.VISIBLE);
        m_scrollSectionSeparator.setVisibility(View.VISIBLE);
    }

    public void dismiss()
    {
        m_view.setVisibility(View.GONE);
    }

    public void onClick(View view)
    {
        if(m_handlingClick)
        {
            return;
        }
        m_handlingClick = true;

        if(view == m_closeButton)
        {
            MyPinDetailsJniMethods.CloseButtonClicked(m_nativeCallerPointer);
        }
        else if(view == m_deleteButton)
        {
            showRemovePinDialog();
        }
    }

    private void showRemovePinDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle("Remove Pin")
        .setMessage("Are you sure you want to remove this pin?")
        .setPositiveButton("Yes,  delete it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int id)
            {
                MyPinDetailsJniMethods.RemovePinButtonClicked(m_nativeCallerPointer);
            }
        })
        .setNegativeButton("No,  keep it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                m_handlingClick = false;
            }
        })
        .setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            @Override
            public void onCancel(DialogInterface dialog)
            {
                m_handlingClick = false;
            }
        });
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
