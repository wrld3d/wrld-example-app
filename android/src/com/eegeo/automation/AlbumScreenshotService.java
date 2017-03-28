// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.automation;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.os.Environment;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;

import com.eegeo.entrypointinfrastructure.MainActivity;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class AlbumScreenshotService
{
    private MainActivity m_activity;
    private long m_nativeCallerPointer;

    public AlbumScreenshotService(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    public void screenshot(final String name)
    {
        AlbumScreenshotServiceJniMethods.AsyncSurfaceScreenshot(m_nativeCallerPointer, new AsyncSurfaceScreenshotCompositor() {
            @Override
            public void run(final long width, final long height, final byte[] surfaceScreenshotBytes)
            {
                m_activity.runOnUiThread(new Runnable() {
                    @Override
                    public void run()
                    {
                        Bitmap decorView = takeScreenshot();
                        Bitmap bitmap = Bitmap.createBitmap((int) width, (int) height, Bitmap.Config.ARGB_8888);
                        bitmap.copyPixelsFromBuffer(ByteBuffer.wrap(surfaceScreenshotBytes));
                        saveScreenshot(screenshotName(name), composite(bitmap, decorView));
                    }
                });
            }
        });
    }

    private Bitmap composite(final Bitmap surface, final Bitmap decor)
    {
        Bitmap compositeBitmap = Bitmap.createBitmap(decor.getWidth(), decor.getHeight(), surface.getConfig());
        Canvas canvas = new Canvas(compositeBitmap);

        Paint paint = new Paint();
        paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.DST_OVER));
        canvas.drawBitmap(decor, 0, 0, paint);

        Matrix m = new Matrix();
        m.setTranslate(0, decor.getHeight() - surface.getHeight());
        canvas.drawBitmap(flipBitmap(surface), m, paint);

        return compositeBitmap;
    }

    private Bitmap takeScreenshot()
    {
        final View rootView = m_activity.getWindow().getDecorView().getRootView();
        rootView.setDrawingCacheEnabled(true);
        Bitmap decorBitmap = Bitmap.createBitmap(rootView.getDrawingCache());
        rootView.setDrawingCacheEnabled(false);
        return decorBitmap;
    }

    private void saveScreenshot(final String name, final Bitmap screenshot)
    {
        m_activity.getRuntimePermissionDispatcher().checkStoragePermissions();
        final String albumDirName = m_activity.getApplicationContext().getPackageName();
        try
        {
            final File albumDir = getAlbumStorageDir(albumDirName);
            if (!albumDir.exists())
            {
                if (!albumDir.mkdirs())
                {
                    Log.e("Eegeo", "Error creating screenshots directory.");
                }
            }
            final File screenshotFile = new File(albumDir, name);
            screenshot.compress(Bitmap.CompressFormat.PNG, 100, new FileOutputStream(screenshotFile));
        }
        catch (IOException e)
        {
            Log.e("Eegeo", "Error taking screenshot `+ " + name + "': " + e.getMessage());
        }
    }

    private static File getAlbumStorageDir(final String albumName)
    {
        return new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES), albumName);
    }

    private static String screenshotName(final String filename)
    {
        return filename + "_" +  System.currentTimeMillis() + ".png";
    }

    private static Bitmap flipBitmap(final Bitmap bitmap)
    {
        Matrix m = new Matrix();
        m.preScale(1, -1);
        Bitmap flipped = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), m, false);
        flipped.setDensity(DisplayMetrics.DENSITY_DEFAULT);
        return flipped;
    }
}
